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
#include "ledMatrix/ledMatrix.h"

// Images 

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

static int tieWord [11 * 3] = {
    1,1,1,8,1,1,1,8,1,1,1,
    8,1,8,8,8,1,8,8,1,1,8,
    8,1,8,8,1,1,1,8,1,1,1,
};

static int loseWord[15 * 3] = {
    1,8,8,8,1,1,1,8,8,1,1,8,1,1,1,
    1,8,8,8,1,8,1,8,8,1,8,8,1,1,8,
    1,1,1,8,1,1,1,8,1,1,8,8,1,1,1,
};

static int sLetter [3 * 3] = {
    8,1,1,
    8,1,8,
    1,1,8,
};

static int sLetterGreen [3 * 3] = {
    8,2,2,
    8,2,8,
    2,2,8,
};

static int rLetter [3 * 3] =  {   
    1,1,1,
    1,8,8,
    1,8,8,  
};

static int rLetterGreen [3 * 3] =  {   
    2,2,2,
    2,8,8,
    2,8,8,  
};

static int pLetter [3 * 3] =  {   
    1,1,1,
    1,1,1,
    1,8,8,  
};

static int pLetterGreen [3 * 3] =  {   
    2,2,2,
    2,2,2,
    2,8,8,  
};

static int scissorsPic [8 * 8] = {
    1,1,1,8,8,8,1,8,
    1,8,1,8,8,1,8,8,
    1,1,1,8,1,8,8,8,
    8,8,8,1,8,8,8,8,
    8,8,8,1,8,8,8,8,
    1,1,1,8,1,8,8,8,
    1,8,1,8,8,1,8,8,
    1,1,1,8,8,8,1,8,
};

static int rockPic [8 * 8] = {
    8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,
    8,8,8,1,1,8,8,8,
    8,1,1,1,1,1,8,8,
    1,1,1,1,1,1,1,8,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
};

static int paperPic [8 * 8] = {
    1,8,1,8,1,8,1,8,
    1,1,1,1,1,1,1,8,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    8,1,1,1,1,1,1,1,
    8,1,8,1,8,1,8,1,
};


typedef enum {
    ROCK,
    PAPER,
    SCISSORS
} RPS_CHOICE;

void rpsGame_Start(void)
{
    srand(time(NULL));
    DigitDisplay_init();
    RPS_CHOICE cpuPick = rand() % 3;
    RPS_CHOICE playerPick = PAPER;

    long long initTime = getTimeInMs();
    long long endTime = initTime + (6000);

    ledMatrix_drawImage(rockPic, 8, 8, 3, 0);
    ledMatrix_drawImage(paperPic, 8, 8, 14, 0);
    ledMatrix_drawImage(scissorsPic, 8, 8, 24, 0);

    ledMatrix_drawImage(rLetter, 3, 3, 5, 11);
    ledMatrix_drawImage(pLetterGreen, 3, 3, 16, 11);
    ledMatrix_drawImage(sLetter, 3, 3, 27, 11);
    ledMatrix_drawHLine(GREEN, 13, 7, 5);

    //0 Left 1 Middle 2 Right
    JoystickDirection input;
    int timerPosition = 0;
    while (getTimeInMs() <= endTime)
    {
        input = Joystick_getDirection();
        if ((playerPick == ROCK && input == JOYSTICK_RIGHT) || (playerPick == SCISSORS && input == JOYSTICK_LEFT))
        {
            playerPick = PAPER;
            ledMatrix_drawImage(pLetterGreen, 3, 3, 16, 11);
            ledMatrix_drawImage(rLetter, 3, 3, 5, 11);
            ledMatrix_drawImage(sLetter, 3, 3, 27, 11);
        }
        else if (playerPick == 1 && input == JOYSTICK_LEFT)
        {
            playerPick = ROCK;
            ledMatrix_drawImage(rLetterGreen, 3, 3, 5, 11);
            ledMatrix_drawImage(pLetter, 3, 3, 16, 11);
            ledMatrix_drawImage(sLetter, 3, 3, 27, 11);

        }
        else if (playerPick == 1 && input == JOYSTICK_RIGHT)
        {
            playerPick = SCISSORS;
            ledMatrix_drawImage(sLetterGreen, 3, 3, 27, 11);
            ledMatrix_drawImage(rLetter, 3, 3, 5, 11);
            ledMatrix_drawImage(pLetter, 3, 3, 16, 11);
        }
        ledMatrix_drawHLine(RED, 13, 7, timerPosition);
        timerPosition = (getTimeInMs() - initTime) / 1000;
        sleepForMs(200);
    }

    ledMatrix_fillScreen(BLACK);

    // Win
    if ((cpuPick == ROCK && playerPick == PAPER) || (cpuPick == SCISSORS && playerPick == ROCK) || (cpuPick == PAPER && playerPick == SCISSORS))
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
    // Tie
    else if (cpuPick == playerPick)
    {

        ledMatrix_drawImage(tieWord, 11, 3, 1, 11);        
        sleepForMs(2000);
        ledMatrix_fillScreen(BLACK);

        Pet_addMood(100);
        Pet_addFriendship(50);

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
    ledMatrix_fillScreen(BLACK);
    DigitDisplay_cleanup();

}

