#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "highLowGame.h"
#include "utils.h"
#include "joystick.h"
#include "digitDisplay.h"
#include "pet.h"
#include "ledMatrix.h"

// Images 

int upArrow [3 * 4] = {
    8,1,8,
    1,1,1,
    8,1,8,
    8,1,0,
};

int downArrow [3 * 4] = {
    8,1,8,
    8,1,8,
    1,1,1,
    8,1,0,
};

int orWord [8 * 3] = {
    1,1,1,8,8,1,1,1,
    1,8,1,8,8,1,8,8,
    1,1,1,8,8,1,8,8,
};

int moodWord [19 * 3] = {
    1,1,1,8,1,1,1,8,1,1,1,8,1,1,8,8,1,1,1,
    1,1,1,8,1,8,1,8,1,8,1,8,1,8,1,8,8,8,8,
    1,8,1,8,1,1,1,8,1,1,1,8,1,1,8,8,1,1,1,
};

int frenWord [19 * 3] = {
    1,1,1,8,1,1,1,8,1,1,1,8,1,1,8,8,1,1,1,
    1,1,8,8,1,8,8,8,1,1,8,8,1,8,1,8,8,8,8,
    1,8,8,8,1,8,8,8,1,1,1,8,1,8,1,8,1,1,1,
};

// Game Thread
static void *hlGameThreadFunction(void *arg);
static pthread_t hlGameThread;

static bool stopping;

void HighLowGame_init(void)
{
    srand(time(NULL));
    stopping = false;
    DigitDisplay_init();
    pthread_create(&hlGameThread, NULL, hlGameThreadFunction, NULL);
}

void HighLowGame_cleanup(void)
{
    stopping = true;
    DigitDisplay_cleanup();
    pthread_join(hlGameThread, NULL);
}

void *hlGameThreadFunction(void *arg)
{
    (void)arg;
    int nextNumber;
    int initNumber = (rand() % 9) + 1;

    do
    {
        nextNumber = (rand() % 9) + 1;
    } while (initNumber == nextNumber);

    sleepForMs(500);
    long long initTime = getTimeInMs();
    long long endTime = initTime + (6000);
    DigitDisplay_setDigit(initNumber);
    JoystickDirection input;
    //Draw things on the LED display
    ledMatrix_drawImage(upArrow, 3, 4, 9, 11);
    ledMatrix_drawImage(orWord, 8, 3, 12, 11);
    ledMatrix_drawImage(downArrow, 3, 4, 20, 11);
    ledMatrix_drawHLine(GREEN, 13, 7, 6);

    char buffer[550];
    ledMatrix_toString(buffer, true);
    ledMatrix_toString(buffer, true);
    // Only checks for up and down
    int timerPosition = 0;
    while (getTimeInMs() <= endTime)
    {
        input = Joystick_getDirection();
        if (input = JOYSTICK_UP || JOYSTICK_DOWN) {
            break;
        }
        ledMatrix_drawHLine(RED, 13, 7, timerPosition);
        timerPosition = (getTimeInMs() - initTime) / 1000;
    }
    DigitDisplay_setDigit(0);
    ledMatrix_fillScreen(BLACK);

    // Win
    if ((initNumber < nextNumber && input == JOYSTICK_UP) || (initNumber > nextNumber && input == JOYSTICK_DOWN))
    {
        Pet_addMood(200);
        Pet_addFriendship(100);
        ledMatrix_drawImage(moodWord, 19, 3, 1, 11);
        DigitDisplay_setDigit(Pet_getMood());
        sleepForMs(2000);

        ledMatrix_fillScreen(BLACK);
        ledMatrix_drawImage(frenWord, 19, 3, 1, 11);
        DigitDisplay_setDigit(Pet_getFriendship());
        sleepForMs(2000);

        ledMatrix_fillScreen(BLACK);
    } 
    // Lose
    else 
    {
        Pet_addMood(-50);
        ledMatrix_drawImage(moodWord, 19, 3, 1, 11);
        DigitDisplay_setDigit(Pet_getMood());
        sleepForMs(2000);
    }

    //TODO: Somehow signal game is done go back to menu 
    
    return NULL;
}