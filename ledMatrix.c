#include "ledMatrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include <stdbool.h>
#include <string.h>
#include <stdatomic.h>

#include <fcntl.h>
#include <time.h>

#include "utils.h"

// ------------------------------------ //
// globals:

#define RED1_PIN 8     // UPPER
#define GREEN1_PIN 80
#define BLUE1_PIN 78
#define RED2_PIN 76    // LOWER
#define GREEN2_PIN 79
#define BLUE2_PIN 74
#define CLK_PIN 73      // Arrival of each data
#define LATCH_PIN 75    // End of a row of data
#define OE_PIN 71       // Transition from one row to another
#define A_PIN 72        // Row select
#define B_PIN 77
#define C_PIN 70

static int fileDesc_red1;
static int fileDesc_blue1;
static int fileDesc_green1;
static int fileDesc_red2;
static int fileDesc_blue2;
static int fileDesc_green2;
static int fileDesc_clk;
static int fileDesc_latch;
static int fileDesc_oe;
static int fileDesc_a;
static int fileDesc_b;
static int fileDesc_c;

#define SCREEN_REFRESH_DELAY_IN_US 50

static int screen[32][16];

const int BLACK  = 0;
const int RED    = 1;
const int GREEN  = 2;
const int YELLOW = 3;
const int BLUE   = 4;
const int PURPLE = 5;
const int CYAN   = 6;
const int WHITE  = 7;
const int TRANSPARENT = 8;

pthread_t screenRefreshLoopThreadID = -1;
atomic_bool stopScreenRefreshLoop = false;

// ---------------------------------- //
// private

void setupPins() {
    printf("setting up pins...\n");
    
    // !Upper led
    bool didExport;
    didExport = exportGpio(RED1_PIN);
    // NOTE: `|` doesn't short circuit, which is what we want
    didExport = didExport | exportGpio(GREEN1_PIN);
    didExport = didExport | exportGpio(BLUE1_PIN);

    // Lower led
    didExport = didExport | exportGpio(RED2_PIN);
    didExport = didExport | exportGpio(GREEN2_PIN);
    didExport = didExport | exportGpio(BLUE2_PIN);

    // Timing
    didExport = didExport | exportGpio(CLK_PIN);
    didExport = didExport | exportGpio(LATCH_PIN);
    didExport = didExport | exportGpio(OE_PIN);

    // Row Select
    didExport = didExport | exportGpio(A_PIN);
    didExport = didExport | exportGpio(B_PIN);
    didExport = didExport | exportGpio(C_PIN);

    if (didExport) {
        struct timespec reqDelay = {4, 0};
        nanosleep(&reqDelay, (struct timespec *) NULL);
    }

    // TODO: do we need to config pins?
    //runCommand("config-pin p8.14 gpio");

    // !Upper led
    setGpioDirection(RED1_PIN,   "out");
    setGpioDirection(GREEN1_PIN, "out");
    setGpioDirection(BLUE1_PIN,  "out");

    // Lower led
    setGpioDirection(RED2_PIN,   "out");
    setGpioDirection(GREEN2_PIN, "out");
    setGpioDirection(BLUE2_PIN,  "out");

    // Timing
    setGpioDirection(CLK_PIN,    "out");
    setGpioDirection(LATCH_PIN,  "out");
    setGpioDirection(OE_PIN,     "out");

    // Row Select
    setGpioDirection(A_PIN, "out");
    setGpioDirection(B_PIN, "out");
    setGpioDirection(C_PIN, "out");
    
    printf("export finished\n");

    const char* S_IWRITE = "S_IWUSR";
    fileDesc_red1   = open("/sys/class/gpio/gpio8/value", O_WRONLY, S_IWRITE);
    fileDesc_green1 = open("/sys/class/gpio/gpio80/value", O_WRONLY, S_IWRITE);
    fileDesc_blue1  = open("/sys/class/gpio/gpio78/value", O_WRONLY, S_IWRITE);
    fileDesc_red2   = open("/sys/class/gpio/gpio76/value", O_WRONLY, S_IWRITE);
    fileDesc_green2 = open("/sys/class/gpio/gpio79/value", O_WRONLY, S_IWRITE);
    fileDesc_blue2  = open("/sys/class/gpio/gpio74/value", O_WRONLY, S_IWRITE);
    fileDesc_clk    = open("/sys/class/gpio/gpio73/value", O_WRONLY, S_IWRITE);
    fileDesc_latch  = open("/sys/class/gpio/gpio75/value", O_WRONLY, S_IWRITE);
    fileDesc_oe = open("/sys/class/gpio/gpio71/value", O_WRONLY, S_IWRITE);
    fileDesc_a  = open("/sys/class/gpio/gpio72/value", O_WRONLY, S_IWRITE);
    fileDesc_b  = open("/sys/class/gpio/gpio77/value", O_WRONLY, S_IWRITE);
    fileDesc_c  = open("/sys/class/gpio/gpio70/value", O_WRONLY, S_IWRITE); 
    
    printf("done pin setup!\n");
}

void* screenRefreshLoop() {
    while (!stopScreenRefreshLoop) {
        ledMatrix_refresh(); // NOTE: this function sleeps for as long as neccesary
    }
    pthread_exit(NULL);
}

// clock the clock pin 1 cycle
void cycleClock() {
    // Bit-bang the clock gpio
    // Notes: Before program writes, must make sure it's on the 0 index
    lseek(fileDesc_clk, 0, SEEK_SET);
    write(fileDesc_clk, "1", 1);
    lseek(fileDesc_clk, 0, SEEK_SET);
    write(fileDesc_clk, "0", 1);
}

// clock the latch pin 1 cycle (signals the end of a row of data)
void cycleLatch() {
    lseek(fileDesc_latch, 0, SEEK_SET);
    write(fileDesc_latch, "1", 1);
    lseek(fileDesc_latch, 0, SEEK_SET);
    write(fileDesc_latch, "0", 1);
}

// Convert integer to bits and put in dest array
void to3Bits(int input, int* dest) {
    dest[0] = input & 1;

    dest[1] = input & 2;
    dest[1] = dest[1] >> 1;

    dest[2] = input & 4;
    dest[2] = dest[2] >> 2;
}

// rowNumber to be inputted to row pins
void selectRow(int rowNum) {
    // Convert rowNum single bits from int
    int arr[3] = {0, 0, 0};
    to3Bits(rowNum, arr);

    // Write on the row pins
    char a_val[2];
    sprintf(a_val, "%d", arr[0]);
    lseek(fileDesc_a, 0, SEEK_SET);
    write(fileDesc_a, a_val, 1);

    char b_val[2];
    sprintf(b_val, "%d", arr[1]);
    lseek(fileDesc_b, 0, SEEK_SET);
    write(fileDesc_b, b_val, 1);

    char c_val[2];
    sprintf(c_val, "%d", arr[2]);
    lseek(fileDesc_c, 0, SEEK_SET);
    write(fileDesc_c, c_val, 1);
}

// Set the colour of the top part of the LED
void setTopColour(int colour) {
    int arr[3] = {0, 0, 0};
    to3Bits(colour, arr);

    // TODO: make this a lil generic
    // Write on the colour pins
    char red1_val[2];
    sprintf(red1_val, "%d", arr[0]);
    lseek(fileDesc_red1, 0, SEEK_SET);
    write(fileDesc_red1, red1_val, 1);

    char green1_val[2];
    sprintf(green1_val, "%d", arr[1]);
    lseek(fileDesc_green1, 0, SEEK_SET);
    write(fileDesc_green1, green1_val, 1);

    char blue1_val[2];
    sprintf(blue1_val, "%d", arr[2]);
    lseek(fileDesc_blue1, 0, SEEK_SET);
    write(fileDesc_blue1, blue1_val, 1);    
}

// Set the colour of the bottom part of the LED
void setBottomColour(int colour) {
    int arr[3] = {0,0,0};
    to3Bits(colour, arr);

    // Write on the colour pins
    char tmpval[2];
    sprintf(tmpval, "%d", arr[0]);
    lseek(fileDesc_red2, 0, SEEK_SET);
    write(fileDesc_red2, tmpval, 1);

    tmpval[0] = 0;
    sprintf(tmpval, "%d", arr[1]);
    lseek(fileDesc_green2, 0, SEEK_SET);
    write(fileDesc_green2, tmpval, 1);

    tmpval[0] = 0;
    sprintf(tmpval, "%d", arr[2]);
    lseek(fileDesc_blue2, 0, SEEK_SET);
    write(fileDesc_blue2, tmpval, 1);      
}

// ---------------------------------- //
// public

void ledMatrix_clearScreen(int colour) {
    memset(screen, colour, sizeof(screen));
}

// NOTE: don't make any of the values go out of bounds. thanks!
void ledMatrix_drawImage(int* colorData, int width, int height, int xoff, int yoff) {
    int i = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (colorData[i] != TRANSPARENT)
                screen[x+xoff][y+yoff] = colorData[i];
            
            i += 1;
        }
    }
}

void ledMatrix_drawImageHFlipped(int* colorData, int width, int height, int xoff, int yoff) {
    int i = 0;
    for (int y = 0; y < height; y++) {
        for (int x = width-1; x >= 0; x--) {
            if (colorData[i] != TRANSPARENT)
                screen[x+xoff][y+yoff] = colorData[i];
            
            i += 1;
        }
    }
}

void ledMatrix_drawHLine(int color, int xpoint, int ypoint, int xlength) {
    if (color == TRANSPARENT) return;
    for (int x = 0; x < xlength; x++) {
        screen[xpoint+x][ypoint] = color;
    }
}

void ledMatrix_drawVLine(int color, int xpoint, int ypoint, int ylength) {
    if (color == TRANSPARENT) return;
    for (int y = 0; y < ylength; y++) {
        screen[xpoint][ypoint+y] = color;
    }
}

void ledMatrix_drawRect(int color, int xpoint, int ypoint, int xlength, int ylength) {
    if (color == TRANSPARENT) return;
    for (int y = 0; y < ylength; y++) {
        for (int x = 0; x < xlength; x++) {
            screen[xpoint+x][ypoint+y] = color;
        }
    }
}

// Set the pixel at x,y with colour
// NOTE: x is the short side, y is the tall side
void ledMatrix_setPixel(int colour, int x, int y) {
    screen[y][x] = colour;
}

// display `screen` to the LED Matrixs' pixels 
void ledMatrix_refresh() {
    for (int rowNum = 0; rowNum < 8; rowNum++) {
        lseek(fileDesc_oe, 0, SEEK_SET);
        write(fileDesc_oe, "1", 1); 

        selectRow(rowNum);
        for (int colNum = 0; colNum < 32; colNum++) {
            setTopColour(screen[colNum][rowNum]);
            setBottomColour(screen[colNum][rowNum+8]);
            cycleClock();
        }

        cycleLatch();
        
        lseek(fileDesc_oe, 0, SEEK_SET);
        write(fileDesc_oe, "0", 1);

        // sleep a few us each 2 rows
        struct timespec reqDelay = {0, SCREEN_REFRESH_DELAY_IN_US};
    	nanosleep(&reqDelay, (struct timespec *) NULL);
    }
}

void ledMatrix_setup() {
    setupPins();
}
void ledMatrix_enable() {
    memset(screen, 0, sizeof(screen));
    pthread_create(&screenRefreshLoopThreadID, NULL, screenRefreshLoop, NULL);
}
void ledMatrix_disable() {
    memset(screen, 0, sizeof(screen));
    sleepForMs(1);
    stopScreenRefreshLoop = true;
    pthread_join(screenRefreshLoopThreadID, NULL);
}
void ledMatrix_cleanup() {
    // TODO: maybe cleanup should just be in disable?
    // cleanup pin file descriptors
    close(fileDesc_red1);
    close(fileDesc_green1);
    close(fileDesc_blue1);
    close(fileDesc_red2);
    close(fileDesc_green2);
    close(fileDesc_blue2);
    close(fileDesc_clk);
    close(fileDesc_latch);
    close(fileDesc_oe);
    close(fileDesc_a);
    close(fileDesc_b);
    close(fileDesc_c);

    // NOTE: prevent any accidental messages being sent?
    setGpioDirection(RED1_PIN,   "in");
    setGpioDirection(GREEN1_PIN, "in");
    setGpioDirection(BLUE1_PIN,  "in");
    setGpioDirection(RED2_PIN,   "in");
    setGpioDirection(GREEN2_PIN, "in");
    setGpioDirection(BLUE2_PIN,  "in");
    setGpioDirection(CLK_PIN,    "in");
    setGpioDirection(LATCH_PIN,  "in");
    setGpioDirection(OE_PIN,     "in");
    setGpioDirection(A_PIN,      "in");
    setGpioDirection(B_PIN,      "in");
    setGpioDirection(C_PIN,      "in");
}

// fills outstr with the level data. Make sure outstr is large enough to fit it! (size must be >= 17 * 32 + 1)
void ledMatrix_toString(char* outstr, bool visibility_mode) {
    int i = 0;
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 32; x++) {
            if (visibility_mode) {
                if (screen[x][y] == RED) {
                    outstr[i] = 'R';
                } else if (screen[x][y] == GREEN) {
                    outstr[i] = 'G';
                } else if (screen[x][y] == BLUE) {
                    outstr[i] = 'B';
                } else if (screen[x][y] == BLACK) {
                    outstr[i] = ' ';
                } else if (screen[x][y] == WHITE) {
                    outstr[i] = '#';
                } else if (screen[x][y] == YELLOW) {
                    outstr[i] = 'Y';
                } else if (screen[x][y] == PURPLE) {
                    outstr[i] = 'P';
                } else if (screen[x][y] == CYAN) {
                    outstr[i] = 'C';
                } else {
                    outstr[i] = '?';
                }
            } else {
                outstr[i] = '0'+screen[x][y];
            }
            i += 1;
        }

        outstr[i] = '\n';
        i += 1;
    } 
    outstr[i] = '\0';
}
