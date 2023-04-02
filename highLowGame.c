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
    long long endTime = initTime + (5000);
    DigitDisplay_setDigit(initNumber);
    JoystickDirection input;

    // Only checks for up and down
    // TODO: Add a visual timer could be just 5 dots
    while (getTimeInMs() <= endTime)
    {
        input = Joystick_getDirection();
        if (input = JOYSTICK_UP || JOYSTICK_DOWN) {
            break;
        }
    }

    // Win
    if ((initNumber < nextNumber && input == JOYSTICK_UP) || (initNumber > nextNumber && input == JOYSTICK_DOWN))
    {
        Pet_addMood(Pet_getMood() + 200);
        Pet_addFriendship(Pet_getFriendship + 100);

        //TODO: Show mood on digit display and write "mood =" to led display do for both 
    } 
    // Lose
    else 
    {
        Pet_addMood(Pet_getMood() - 50);
    }

    //TODO: Somehow signal game is done go back to menu 
    
    return NULL;
}