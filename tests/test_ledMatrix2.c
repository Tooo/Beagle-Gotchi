// test_ledMatrix2.c
// This file tests writing colours & animations using ledMatrix.h

#include "../ledMatrix/ledMatrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <stdbool.h>
#include <string.h>
#include <stdatomic.h>

#include <fcntl.h>
#include <time.h>

#include "../utils/utils.h"

// ------------------------------------ //
// functionality:

int main() {
    ledMatrix_setup();

    for (int frame = 0; frame < 25 * 10; frame++) {
        ledMatrix_fillScreen(BLACK);

        //ledMatrix_setPixel((frame / 32) % 16, frame % 32, (frame) % 8);
        //for (int head = 0; head < 120; head++) {
            //ledMatrix_setPixel(((frame+head) / 32) % 16, (frame+head) % 32, (frame+head) % 7 + 1);
        //    ledMatrix_setPixel(((frame+head) / 32) % 16, (frame+head) % 32, ((frame+head)/7) % 8);
        //}
        //for (int j = 0; j < 8; j++) {
        //    for (int i = 0; i < 16; i++) {
        //        int t = (frame%16) < 8 ? frame%8 : 8-(frame%8);
        //    }
        //}

        for (int j = 0; j < 8; j++) {
            for (int i = 0; i < 16; i++) {
                int t = (frame%16) < 8 ? frame%8 : 8-(frame%8);
                ledMatrix_setPixel(j, i, i+j+t);
            }
        }

        sleepForMs(40);
    }

    ledMatrix_cleanup();
    return 1;
}