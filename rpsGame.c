#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rpsGame.h"
#include "utils.h"
#include "joystick.h"
#include "digitDisplay.h"
#include "pet.h"
#include "ledMatrix.h"

// Images 

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
static pthread_t rpsGameThread;

typedef enum {
    ROCK,
    PAPER,
    SCISSORS
} RPS_CHOICE;

static bool stopping;

void rpsGame_init(void)
{
    srand(time(NULL));
    stopping = false;
    DigitDisplay_init();
    pthread_create(&rpsGameThread, NULL, rpsGameThreadFunction, NULL);
}

void rpsGame_cleanup(void)
{
    stopping = true;
    DigitDisplay_cleanup();
    pthread_join(rpsGameThread, NULL);
    DigitDisplay_setDigit(0);

    
}

void *rpsGameThreadFunction(void *arg)
{
    (void)arg;
    RPS_CHOICE cpuPick = rand() % 3;
    RPS_CHOICE playerPick = PAPER;

    long long initTime = getTimeInMs();
    long long endTime = initTime + (6000);

    //TODO Draw rps
    ledMatrix_drawHLine(GREEN, 13, 7, 6);

    //0 Left 1 Middle 2 Right
    JoystickDirection input;
    int timerPosition = 0;
    while (getTimeInMs() <= endTime)
    {
        input = Joystick_getDirection();
        if ((playerPick == ROCK && input == JOYSTICK_RIGHT) || (playerPick == SCISSORS && input == JOYSTICK_LEFT))
        {
            playerPick = PAPER;
            //change the color of the picked 
        }
        else if (playerPick == 1 && input == JOYSTICK_LEFT)
        {
            playerPick = ROCK;
            //change color 
        }
        else if (playerPick == 1 && input == JOYSTICK_RIGHT)
        {
            playerPick = SCISSORS;
            //change color 
        }
        ledMatrix_drawHLine(RED, 13, 7, timerPosition);
        timerPosition = (getTimeInMs() - initTime) / 1000;
    }
    // Win
    if ((cpuPick == ROCK && playerPick == PAPER) || (cpuPick == SCISSORS && playerPick == ROCK) || (cpuPick == PAPER && playerPick == SCISSORS))
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
    // Tie
    else if (cpuPick == playerPick)
    {
        Pet_addMood(100);
        Pet_addFriendship(50);

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