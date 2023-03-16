// test_ledAnimation.c
// This file tests reading from files & playing an animations using ledMatrix.h

#include "../ledMatrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <stdbool.h>
#include <string.h>
#include <stdatomic.h>

#include <fcntl.h>
#include <time.h>

#include "../utils.h"

// ------------------------------------ //
// images:

int exclamation[5 * 5] = {
    1,8,1,8, 1,
    1,8,1,8, 1,
    1,8,1,8, 1,
    8,8,8,8, 8,

    1,8,1,8, 1,
};

int heart[5 * 5] = {
    8,1,8,1, 8,
    1,1,1,1, 1,
    1,1,1,1, 1,
    8,1,1,1, 8,

    8,8,1,8, 8,
};

int heartSmall[3 * 2] = {
    1,8,1,
    8,1,8,
};

int dogframe1[15 * 9] = {
    8,8,8,8, 8,8,8,8, 4,8,8,8, 4,8,8,
    8,8,8,8, 8,8,8,8, 4,4,4,4, 4,8,8,
    4,4,8,4, 4,4,4,4, 4,4,7,4, 7,8,8,
    8,4,4,4, 4,4,4,4, 4,4,4,4, 4,4,8,
    
    8,8,4,4, 4,4,4,4, 4,4,4,4, 7,7,4,
    8,8,4,4, 4,4,4,4, 4,7,4,4, 4,4,8,
    8,8,7,4, 4,7,7,7, 4,4,7,7, 7,8,8,
    8,8,4,4, 7,4,8,8, 4,4,8,4, 4,8,8,
    
    8,8,7,8, 8,7,8,8, 7,8,8,8, 7,8,8
};
int dogframe2[15 * 9] = {
    8,8,8,8, 8,8,8,8, 4,8,8,8, 4,8,8,
    4,8,8,8, 8,8,8,8, 4,4,4,4, 4,8,8,
    8,4,8,4, 4,4,4,4, 4,4,7,4, 7,8,8,
    8,4,4,4, 4,4,4,4, 4,4,4,4, 4,4,8,
    
    8,8,4,4, 4,4,4,4, 4,4,4,4, 7,7,4,
    8,8,4,4, 4,4,4,4, 4,7,4,4, 4,4,8,
    8,8,7,4, 4,7,7,7, 4,4,7,7, 8,8,8,
    8,8,4,7, 4,4,8,4, 7,4,4,8, 8,8,8,
    
    8,8,7,8, 8,7,8,7, 8,8,7,8, 8,8,8
};
int dogframe3[15 * 9] = {
    8,8,8,8, 8,8,8,8, 4,8,8,8, 4,8,8,
    8,8,8,8, 8,8,8,8, 4,4,4,4, 4,8,8,
    4,4,8,4, 4,4,4,4, 4,4,7,4, 7,8,8,
    8,4,4,4, 4,4,4,4, 4,4,4,4, 4,4,8,
    
    8,8,4,4, 4,4,4,4, 4,4,4,4, 7,7,4,
    8,8,4,4, 4,4,4,4, 4,7,7,4, 4,4,8,
    8,8,8,4, 4,7,7,7, 7,4,4,7, 4,8,8,
    8,8,8,4, 7,4,8,8, 8,4,7,4, 8,8,8,
    
    8,8,8,4, 7,4,8,8, 8,4,7,4, 8,8,8
};
int dogframetail2[15 * 9] = {
    8,8,8,8, 8,8,8,8, 4,8,8,8, 4,8,8,
    4,8,8,8, 8,8,8,8, 4,4,4,4, 4,8,8,
    8,4,8,8, 4,4,4,4, 4,4,7,4, 7,8,8,
    8,4,4,4, 4,4,4,4, 4,4,4,4, 4,4,8,
    
    8,8,4,4, 4,4,4,4, 4,4,4,4, 7,7,4,
    8,8,4,4, 4,4,4,4, 4,7,4,4, 4,4,8,
    8,8,7,4, 4,7,7,7, 4,4,7,7, 7,8,8,
    8,8,4,4, 7,4,8,8, 4,4,8,4, 4,8,8,
    
    8,8,7,8, 8,7,8,8, 7,8,8,8, 7,8,8
};

// ------------------------------------ //
// functionality:

int main() {
    ledMatrix_setup();
    ledMatrix_enable();

    // state variables
    int xpos = 1;
    int ypos = 5;

    bool h1_visible = false;
    bool h2_visible = false;
    int hy1 = 2;
    int hx1 = 23;
    int hy2 = 5;
    int hx2 = 19;

    for (int frame = 0; frame < 25 * 10; frame++) {
        // fill screen with cyan
        ledMatrix_clearScreen(BLACK);

        // draw ground
        ledMatrix_drawHLine(GREEN, 0, 14, 31);
        ledMatrix_drawHLine(GREEN, 0, 15, 31);

        // main animation
        if (frame < 12) {
            // drawn animal
            if (frame % 3 == 0)
                ledMatrix_drawImage(dogframe1, 15, 9, xpos, ypos);
            else if (frame % 3 == 1) 
                ledMatrix_drawImage(dogframe2, 15, 9, xpos, ypos);
            else if (frame % 3 == 2)
                ledMatrix_drawImage(dogframe3, 15, 9, xpos, ypos);

            xpos += 1;
        } else if (frame < 15) {
            if (frame % 2 == 0)
                ledMatrix_drawImage(dogframe1, 15, 9, xpos, ypos);
            else 
                ledMatrix_drawImage(dogframetail2, 15, 9, xpos, ypos);
        } else if (frame < 17) {
            ledMatrix_drawImage(dogframe1, 15, 9, xpos, ypos);
            ypos -= 2;
        } else if (frame < 19) {
            ledMatrix_drawImage(dogframe1, 15, 9, xpos, ypos);
            ypos += 2;
        } else if (frame < 19+3) {
            if (frame % 2 == 0)
                ledMatrix_drawImage(dogframe1, 15, 9, xpos, ypos);
            else 
                ledMatrix_drawImage(dogframetail2, 15, 9, xpos, ypos);
        } else if (frame < 19+3+2) {
            ledMatrix_drawImage(dogframe1, 15, 9, xpos, ypos);
            ypos -= 2;
        } else if (frame < 19+3+2+2) {
            ledMatrix_drawImage(dogframe1, 15, 9, xpos, ypos);
            ypos += 2;
        } else if (frame < 80) {
            if (frame % 4 == 0 || frame % 4 == 1)
                ledMatrix_drawImage(dogframetail2, 15, 9, xpos, ypos);
            else 
                ledMatrix_drawImage(dogframe1, 15, 9, xpos, ypos);

            // animate both hearts
            if (frame > 30) {
                {
                    if (frame % 30 == 3) {
                        h1_visible = true;
                        hy1 = 2;
                    }
                    
                    if (h1_visible) {
                        ledMatrix_drawImage(heart, 5, 5, hx1, hy1);

                        if (frame % 3 == 0)
                            hy1 += 1;

                        if (frame % 4 == 0)
                            hx1 += 1;
                        else if (frame % 4 == 2)
                            hx1 -= 1;
                    }

                    if (hy1 > 9) {
                        h1_visible = false;
                    }
                }

                {
                    if (frame % 30 == 15) {
                        h2_visible = true;
                        hy2 = 2;
                    }
                    
                    if (h2_visible) {
                        ledMatrix_drawImage(heartSmall, 3, 2, hx2, hy2);

                        if ((frame+1) % 3 == 0)
                            hy2 += 1;

                        if ((frame+1) % 4 == 0)
                            hx2 += 1;
                        else if ((frame+1) % 4 == 2)
                            hx2 -= 1;
                    }

                    if (hy2 > 13) {
                        h2_visible = false;
                    }
                }
            }
        } else if (frame < 89) {
            ledMatrix_drawImage(dogframe1, 15, 9, xpos, ypos);
            ledMatrix_drawImage(exclamation, 5, 5, xpos + 13, 2);
        } else if ((xpos - 3) > 0) {
            if (frame % 3 == 0)
                ledMatrix_drawImageHFlipped(dogframe1, 15, 9, xpos, ypos);
            else if (frame % 3 == 1) 
                ledMatrix_drawImageHFlipped(dogframe2, 15, 9, xpos, ypos);
            else if (frame % 3 == 2)
                ledMatrix_drawImageHFlipped(dogframe3, 15, 9, xpos, ypos);
            ledMatrix_drawImage(exclamation, 5, 5, xpos - 3, 2);
            xpos -= 1;
        } else if (xpos > 1) {
            if (frame % 3 == 0)
                ledMatrix_drawImageHFlipped(dogframe1, 15, 9, xpos, ypos);
            else if (frame % 3 == 1) 
                ledMatrix_drawImageHFlipped(dogframe2, 15, 9, xpos, ypos);
            else if (frame % 3 == 2)
                ledMatrix_drawImageHFlipped(dogframe3, 15, 9, xpos, ypos);
            xpos -= 1;
        } else if (frame < 100) {
            if (frame % 4 == 0 || frame % 4 == 1)
                ledMatrix_drawImageHFlipped(dogframetail2, 15, 9, xpos, ypos);
            else 
                ledMatrix_drawImageHFlipped(dogframe1, 15, 9, xpos, ypos);
        } else {
            if (frame % 4 == 0 || frame % 4 == 1)
                ledMatrix_drawImage(dogframetail2, 15, 9, xpos, ypos);
            else 
                ledMatrix_drawImage(dogframe1, 15, 9, xpos, ypos);
        }

        printf("frame: %d\n", frame);

        sleepForMs(80);
    }

    ledMatrix_disable();
    ledMatrix_cleanup();
    return 1;
}