/********************************************************************
 *  File Name: test_ledMatrix.c
 *  Description: A simple program to display pattern on LED Matrix
 *  
 *  About 80% of the code converted from Python to C, source:
 *      https://learn.adafruit.com/connecting-a-16x32-rgb-led-matrix-panel-to-a-raspberry-pi/experimental-python-code
 *-------------------------------------------------------------------
 *  Created by: Janet mardjuki
 *  Date: 3 December 2015
 *  
 *  Modified by: Raymond Chan
 *  Date: 2 August 2018
 ********************************************************************/
// NOTE: please run program twice in order to "double export" pins
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

/*** GLOBAL VARIABLE ***/
/* GPIO PATH */
#define GPIO_PATH "/sys/class/gpio/"

/* GPIO Pins Definition */
#define RED1_PIN 8     // UPPER
#define GREEN1_PIN 80
#define BLUE1_PIN 78
#define RED2_PIN 76 // LOWER
#define GREEN2_PIN 79
#define BLUE2_PIN 74
#define CLK_PIN 73      // Arrival of each data
#define LATCH_PIN 75    // End of a row of data
#define OE_PIN 71       // Transition from one row to another
#define A_PIN 72        // Row select
#define B_PIN 77
#define C_PIN 70

#define S_IWRITE "S_IWUSR"

/* TIMING */
#define DELAY_IN_US 10
#define DELAY_IN_SEC 0

/* LED Screen Values */
static int screen[32][16];

/* FILES HANDLER */
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

static void setExport(int pinNum) {
    // Export the gpio pins
    FILE *gpioExP = fopen(GPIO_PATH "export", "w");
    if ( gpioExP == NULL ){
        printf("ERROR: Unable to open export file.\n");
        exit(-1);
    }
    fprintf(gpioExP, "%d", pinNum);
    fclose(gpioExP);
    
    return;
}

static void setOut(int pinNum) {
    // Change the direction into out
    char fileNameBuffer[1024];
    sprintf(fileNameBuffer, GPIO_PATH "gpio%d/direction", pinNum);
        
    FILE *gpioDirP = fopen(fileNameBuffer, "w");
    fprintf(gpioDirP, "out");
    fclose(gpioDirP);
    return;
}

/**
 * setupPins
 * Setup the pins used by the led matrix, by exporting and set the direction to out
 */
static void setupPins(void) {
    printf("Exporting pins...\n");
    // !Upper led
    setExport(RED1_PIN);
    setExport(GREEN1_PIN);
    setExport(BLUE1_PIN);

    // Lower led
    setExport(RED2_PIN);
    setExport(GREEN2_PIN);
    setExport(BLUE2_PIN);

    // Timing
    setExport(CLK_PIN);
    setExport(LATCH_PIN);
    setExport(OE_PIN);

    // Row Select
    setExport(A_PIN);
    setExport(B_PIN);
    setExport(C_PIN);

    struct timespec reqDelay = {4, 0};
	nanosleep(&reqDelay, (struct timespec *) NULL);

    // !Upper led
    setOut(RED1_PIN);
    setOut(GREEN1_PIN);
    setOut(BLUE1_PIN);

    // Lower led
    setOut(RED2_PIN);
    setOut(GREEN2_PIN);
    setOut(BLUE2_PIN);

    // Timing
    setOut(CLK_PIN);
    setOut(LATCH_PIN);
    setOut(OE_PIN);

    // Row Select
    setOut(A_PIN);
    setOut(B_PIN);
    setOut(C_PIN);

    fileDesc_red1 = open("/sys/class/gpio/gpio8/value", O_WRONLY, S_IWRITE);
    fileDesc_green1 = open("/sys/class/gpio/gpio80/value", O_WRONLY, S_IWRITE);
    fileDesc_blue1 = open("/sys/class/gpio/gpio78/value", O_WRONLY, S_IWRITE);
    fileDesc_red2 = open("/sys/class/gpio/gpio76/value", O_WRONLY, S_IWRITE);
    fileDesc_green2 = open("/sys/class/gpio/gpio79/value", O_WRONLY, S_IWRITE);
    fileDesc_blue2 = open("/sys/class/gpio/gpio74/value", O_WRONLY, S_IWRITE);
    fileDesc_clk = open("/sys/class/gpio/gpio73/value", O_WRONLY, S_IWRITE);
    fileDesc_latch = open("/sys/class/gpio/gpio75/value", O_WRONLY, S_IWRITE);
    fileDesc_oe = open("/sys/class/gpio/gpio71/value", O_WRONLY, S_IWRITE);
    fileDesc_a = open("/sys/class/gpio/gpio72/value", O_WRONLY, S_IWRITE);
    fileDesc_b = open("/sys/class/gpio/gpio77/value", O_WRONLY, S_IWRITE);
    fileDesc_c = open("/sys/class/gpio/gpio70/value", O_WRONLY, S_IWRITE); 
    
    printf("Export Finished!\n");
    return;
}


/** 
 *  ledMatrix_clock
 *  Generate the clock pins
 */
static void ledMatrix_clock(void)
{
    // Bit-bang the clock gpio
    // Notes: Before program writes, must make sure it's on the 0 index
    lseek(fileDesc_clk, 0, SEEK_SET);
    write(fileDesc_clk, "1", 1);
    lseek(fileDesc_clk, 0, SEEK_SET);
    write(fileDesc_clk, "0", 1);

    return;
}

/**
 *  ledMatrix_latch
 *  Generate the latch pins
 */
static void ledMatrix_latch(void)
{
    lseek(fileDesc_latch, 0, SEEK_SET);
    write(fileDesc_latch, "1", 1);
    lseek(fileDesc_latch, 0, SEEK_SET);
    write(fileDesc_latch, "0", 1);

    return;
}

/**
 *  ledMatrix_bitsFromInt
 *  Convert integer passed on into bits and put in array
 *  @params:
 *      int * arr: pointer to array to be filled with bits
 *      int input: integer to be converted to bits
 */
static void ledMatrix_bitsFromInt(int * arr, int input)
{
    arr[0] = input & 1;

    arr[1] = input & 2;
    arr[1] = arr[1] >> 1;

    arr[2] = input & 4;
    arr[2] = arr[2] >> 2;

    return;
}

/**
 *  ledMatrix_setRow
 *  Set LED Matrix row
 *  @params:
 *      int rowNum: the rowNumber to be inputted to row pins
 */
static void ledMatrix_setRow(int rowNum)
{
    // Convert rowNum single bits from int
    int arr[3] = {0, 0, 0};
    ledMatrix_bitsFromInt(arr, rowNum);

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


    return;
}

/**
 *  ledMatrix_setColorTop
 *  Set the color of the top part of the LED
 *  @params:
 *      int color: color to be set
 */
static void ledMatrix_setColorTop(int color)
{
    int arr[3] = {0, 0, 0};
    ledMatrix_bitsFromInt(arr, color);

    // Write on the color pins
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

    return;
}

/**
 *  ledMatrix_setColorBottom
 *  Set the color of the bottom part of the LED
 *  @params:
 *      int color: color to be set
 */
static void ledMatrix_setColorBottom(int color)
{
    int arr[3] = {0,0,0};
    ledMatrix_bitsFromInt(arr, color);

    // Write on the color pins
    char red2_val[2];
    sprintf(red2_val, "%d", arr[0]);
    lseek(fileDesc_red2, 0, SEEK_SET);
    write(fileDesc_red2, red2_val, 1);

    char green2_val[2];
    sprintf(green2_val, "%d", arr[1]);
    lseek(fileDesc_green2, 0, SEEK_SET);
    write(fileDesc_green2, green2_val, 1);

    char blue2_val[2];
    sprintf(blue2_val, "%d", arr[2]);
    lseek(fileDesc_blue2, 0, SEEK_SET);
    write(fileDesc_blue2, blue2_val, 1);      

    return;
}
/**
 *  ledMatrix_refresh
 *  Fill the LED Matrix with the respective pixel color
 */
static void ledMatrix_refresh(void)
{
    for ( int rowNum = 0; rowNum < 8; rowNum++ ) {
        lseek(fileDesc_oe, 0, SEEK_SET);
        write(fileDesc_oe, "1", 1); 
        ledMatrix_setRow(rowNum);
        for ( int colNum = 0; colNum < 32;  colNum++) {
            ledMatrix_setColorTop(screen[colNum][rowNum]);
            ledMatrix_setColorBottom(screen[colNum][rowNum+8]);
            ledMatrix_clock();
        }
        ledMatrix_latch();
        lseek(fileDesc_oe, 0, SEEK_SET);
        write(fileDesc_oe, "0", 1); 
        struct timespec reqDelay = {DELAY_IN_SEC, DELAY_IN_US}; // sleep for delay
    	nanosleep(&reqDelay, (struct timespec *) NULL);
    }
    return;
}

/**
 *  ledMatrix_setPixel
 *  Set the pixel selected on LED MAtrix with the color selected
 *  @params:
 *      int x: x-axis
 *      int y: y-axis
 *      int color: color selected
 */
static void ledMatrix_setPixel(int x, int y, int color)
{
    screen[y][x] = color;

    return;
}

/*** MAIN ***/
int main()
{   
    // Reset the screen
    memset(screen, 0, sizeof(screen));

    // Setup pins
    setupPins();
   
    for ( int i = 0; i < 16; i++ ) {
        ledMatrix_setPixel(i, i, 1);
        ledMatrix_setPixel(i, 32-1-i , 2);
    }

    printf("Starting the program\n");
    while(1) {
        ledMatrix_refresh();
    }

    return 0;
}

