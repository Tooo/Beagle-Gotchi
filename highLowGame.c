#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "highLowGame.h"
#include "utils.h"
#include "hardware/joystick.h"
#include "hardware/digitDisplay.h"
#include "pet.h"
#include "ledMatrix/ledMatrix.h"

// Images 

static int upArrow [3 * 4] = {
    8,1,8,
    1,1,1,
    8,1,8,
    8,1,0,
};

static int downArrow [3 * 4] = {
    8,1,8,
    8,1,8,
    1,1,1,
    8,1,0,
};

static int orWord [8 * 3] = {
    1,1,1,8,8,1,1,1,
    1,8,1,8,8,1,8,8,
    1,1,1,8,8,1,8,8,
};

static int moodWord [20 * 3] = {
    1,1,1,8,1,1,1,8,1,1,1,8,1,1,8,8,8,8,1,8,
    1,1,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,1,1,1,
    1,8,1,8,1,1,1,8,1,1,1,8,1,1,8,8,8,8,1,8,
};

static int frenWord [20 * 3] = {
    1,1,1,8,1,1,1,8,1,1,1,8,1,1,8,8,8,8,1,8,
    1,1,8,8,1,8,8,8,1,1,8,8,1,8,1,8,1,1,1,1,
    1,8,8,8,1,8,8,8,1,1,1,8,1,8,1,8,8,8,1,8,
};

static int winWord [11 * 3] = {
    1,8,1,8,1,1,1,8,1,1,8,
    1,1,1,8,8,1,8,8,1,8,1,
    1,1,1,8,1,1,1,8,1,8,1,
};

static int loseWord[15 * 3] = {
    1,8,8,8,1,1,1,8,8,1,1,8,1,1,1,
    1,8,8,8,1,8,1,8,8,1,8,8,1,1,8,
    1,1,1,8,1,1,1,8,1,1,8,8,1,1,1,
};

void HighLowGame_Start(void)
{
    srand(time(NULL));
    DigitDisplay_init();

    int nextNumber;
    int initNumber = (rand() % 9) + 1;

    do
    {
        nextNumber = (rand() % 9) + 1;
    } while (initNumber == nextNumber);

    long long initTime = getTimeInMs();
    long long endTime = initTime + 5000;
    DigitDisplay_setDigit(initNumber);
    JoystickDirection input;

    // Draw to the LED display
    ledMatrix_drawImage(upArrow, 3, 4, 7, 11);
    ledMatrix_drawImage(orWord, 8, 3, 12, 11);
    ledMatrix_drawImage(downArrow, 3, 4, 22, 11);
    ledMatrix_drawHLine(GREEN, 13, 7, 6);

    // Only checks for up and down
    int timerPosition = 0;
    while (getTimeInMs() <= endTime)
    {
        input = Joystick_getDirection();
        if (input == JOYSTICK_UP || input == JOYSTICK_DOWN) {
            break;
        }
        ledMatrix_drawHLine(RED, 13, 7, timerPosition);
        
        timerPosition = (getTimeInMs() - initTime) / 1000;
        sleepForMs(8);
    }
    DigitDisplay_setDigit(0);
    ledMatrix_fillScreen(BLACK);

    // Win
    if ((initNumber <= nextNumber && input == JOYSTICK_UP) || 
        (initNumber >= nextNumber && input == JOYSTICK_DOWN))
    {
        ledMatrix_drawImage(winWord, 11, 3, 1, 11);        
        sleepForMs(2000);
        ledMatrix_fillScreen(BLACK);

        Pet_addMood(200);
        Pet_addFriendship(100);
        ledMatrix_drawImage(moodWord, 20, 3, 1, 11);
        DigitDisplay_setDigit(Pet_getMood());
        sleepForMs(2000);

        ledMatrix_fillScreen(BLACK);
        ledMatrix_drawImage(frenWord, 20, 3, 1, 11);
        DigitDisplay_setDigit(Pet_getFriendship());
        sleepForMs(2000);

        ledMatrix_fillScreen(BLACK);
    } 
    // Lose
    else 
    {
        ledMatrix_drawImage(loseWord, 15, 3, 1, 11);        
        sleepForMs(2000);
        ledMatrix_fillScreen(BLACK);

        Pet_addMood(-50);
        ledMatrix_drawImage(moodWord, 20, 3, 1, 11);
        DigitDisplay_setDigit(Pet_getMood());
        sleepForMs(2000);
    }

    DigitDisplay_cleanup();
    ledMatrix_fillScreen(BLACK);
}
