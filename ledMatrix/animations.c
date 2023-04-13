#include "animations.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>
#include <time.h>

#include "../utils/utils.h"
#include "../hardware/waterSensor.h"

#include "ledMatrix.h"
#include "sprites.h"


const int DEFAULT_FRAME_SPEED = 35; // ~28fps

// ----------------------------
// private

void drawBackground() {
    // ground
    ledMatrix_drawHLine(GREEN, 0, 14, 32);
    ledMatrix_drawHLine(GREEN, 0, 15, 32);

    // sun
    ledMatrix_drawRect(YELLOW, 0, 0, 5, 5);

    ledMatrix_drawVLine(YELLOW, 0, 6, 2);
    ledMatrix_drawVLine(YELLOW, 2, 6, 2);
    ledMatrix_drawVLine(YELLOW, 4, 6, 2);

    ledMatrix_drawHLine(YELLOW, 6, 0, 2);
    ledMatrix_drawHLine(YELLOW, 6, 2, 2);
    ledMatrix_drawHLine(YELLOW, 6, 4, 2);
}

void dogWalkRight(int speed, int frame, int dogX, int dogY) {
    if (between(frame % (speed*3), 0, speed-1)) {
        ledMatrix_drawImage(DOG_FRAME_1, 15, 9, dogX, dogY);
    } else if (between(frame % (speed*3), speed, 2*speed-1)) {
        ledMatrix_drawImage(DOG_FRAME_2, 15, 9, dogX, dogY);
    } else {
        ledMatrix_drawImage(DOG_FRAME_3, 15, 9, dogX, dogY);
    }
}

void dogIdleRight(int speed, int frame, int dogX, int dogY) {
    if (between(frame % (speed*2), 0, speed-1)) {
        ledMatrix_drawImage(DOG_FRAME_1, 15, 9, dogX, dogY);
    } else {
        ledMatrix_drawImage(DOG_TAIL_FRAME, 15, 9, dogX, dogY);
    }
}

// ----------------------------
// public

void animations_playPettingAnimation(int frameTimeInMs) {
    int dogX = 1;
    int dogY = 5;

    int handX = 20;
    int handY = 1;

    int heartX = 13;
    int heartY = 8;

    const int NUM_FRAMES = 28 * 4 + 6;
    for (int frame = 0; frame < NUM_FRAMES; frame++) {
        ledMatrix_fillScreen(BLACK);
        drawBackground();

        dogIdleRight(5, frame, dogX, dogY);

        ledMatrix_drawImage(HAND_SPRITE, HAND_WIDTH, HAND_HEIGHT, handX, handY);

        if (frame < 12 + 16 * 3 + 8 + 4 + 8 + 4 + 4) {

        } else if (frame < 12 + 16 * 3 + 8 + 4 + 8 + 8 + 4) {
            dogY -= 1;
        } else if (frame < 12 + 16 * 3 + 8 + 4 + 8 + 12 + 4) {
            dogY += 1;
        }

        if (frame < 5) { } 
        else if (frame < 12) { handX -= 1; } 
        else if (frame < 12 + 16 * 3) {
            if (frame < 12+3) {
                handX -= 1;
            } else if (frame < 12+3+5) {
                handX -= 1;
                handY += 1;
            } else if (frame < 12+3+5+5) {
                handX += 1;
                handY -= 1;
            } else if (frame < 12+3+5+5+3) {
                handX += 1;
            } 
            
            else if (frame < 15 + 16) {
                handX -= 1;
            } else if (frame < 20 + 16) {
                handX -= 1;
                handY += 1;
            } else if (frame < 25 + 16) {
                handX += 1;
                handY -= 1;
            } else if (frame < 28 + 16) {
                handX += 1;
            } 
            
            else if (frame < 15 + 2 * 16) {
                handX -= 1;
            } else if (frame < 20 + 2 * 16) {
                handX -= 1;
                handY += 1;
            } else if (frame < 25 + 2 * 16) {
                handX += 1;
                handY -= 1;
            } else if (frame < 28 + 2 * 16) {
                handX += 1;
            }
        } else if (frame < 12 + 16 * 3 + 8) {
            handX += 1;
        } else if (frame < 12 + 16 * 3 + 8 + 4) {
            // pause
        } else if (frame < 12 + 16 * 3 + 8 + 4 + 8) {
            ledMatrix_drawImage(HEART_SPRITE, HEART_WIDTH, HEART_HEIGHT, heartX, heartY);
            heartY -= 1;
        } else if (frame < 12 + 16 * 3 + 8 + 4 + 8 + 1) {
            ledMatrix_drawImage(HEART_SPRITE, HEART_WIDTH, HEART_HEIGHT, heartX, heartY);
        } else if (frame < 12 + 16 * 3 + 8 + 4 + 8 + 1 + 1) {
            ledMatrix_drawImage(HEART_SPRITE, HEART_WIDTH, HEART_HEIGHT, heartX, heartY);
            heartY += 1;
        } else {
            ledMatrix_drawImage(HEART_SPRITE, HEART_WIDTH, HEART_HEIGHT, heartX, heartY);
        }
        
        sleepForMs(frameTimeInMs);
    }

    ledMatrix_animateRightWipe(DEFAULT_WIPE_SPEED);
}
void animations_playSlappingAnimation(int frameTimeInMs) {
    int dogX = 1;
    int dogY = 5;

    int handX = 22;
    int handY = 1;

    int sadX = 15;
    int sadY = 6;

    const int NUM_FRAMES = 28 * 2 + 10;
    for (int frame = 0; frame < NUM_FRAMES; frame++) {
        ledMatrix_fillScreen(BLACK);
        drawBackground();

        if (frame < 27) {
            dogIdleRight(5, frame, dogX, dogY);
        } else {
            ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY);
        }

        ledMatrix_drawImage(HAND_SPRITE, HAND_WIDTH, HAND_HEIGHT, handX, handY);

        if (frame == 18) {
            dogX -= 1;
        } else if (frame == 25) {
            dogX += 1;
        } 

        if (frame < 5) { } 
        else if (frame < 10) { handY += 1; } 
        else if (frame < 11) { handX += 1; } 
        else if (frame < 12) { handX -= 4; } 
        else if (frame < 10 + 7) { handX -= 3; } 
        else if (frame < 10 + 7 + 5) { handX += 3; } 
        else if (frame < 10 + 7 + 6) { handX += 2; } 
        else if (frame < 10 + 7 + 7) { handX += 1; } 
        else if (frame < 10 + 7 + 7 + 8 + 4) {
            // pause
        } else if (frame < 10 + 7 + 7 + 8 + 4 + 6) {
            ledMatrix_drawImage(SAD_SPRITE, SAD_WIDTH, SAD_HEIGHT, sadX, sadY);
            sadY -= 1;
        } else if (frame < 10 + 7 + 7 + 8 + 4 + 6 + 1) {
            ledMatrix_drawImage(SAD_SPRITE, SAD_WIDTH, SAD_HEIGHT, sadX, sadY);
        } else if (frame < 10 + 7 + 7 + 8 + 4 + 6 + 1 + 1) {
            ledMatrix_drawImage(SAD_SPRITE, SAD_WIDTH, SAD_HEIGHT, sadX, sadY);
            sadY += 1;
        } else {
            ledMatrix_drawImage(SAD_SPRITE, SAD_WIDTH, SAD_HEIGHT, sadX, sadY);
        }
        
        sleepForMs(frameTimeInMs);
    }

    ledMatrix_animateRightWipe(DEFAULT_WIPE_SPEED);
}

void animations_playMealAnimation(int frameTimeInMs) {
    int dogX = 1;
    int dogY = 5;

    int berryX[3] = { 18, 23, 21 };
    int berryY[3] = { 1, 2, 0 };
    
    bool happyVisible = false;

    const int NUM_FRAMES = 28 * 3 + 10;
    for (int frame = 0; frame < NUM_FRAMES; frame++) {
        ledMatrix_fillScreen(BLACK);
        drawBackground();

        ledMatrix_drawImage(BERRY_SPRITE, BERRY_HEIGHT, BERRY_WIDTH, berryX[2], berryY[2]);
        ledMatrix_drawImage(BERRY_SPRITE, BERRY_HEIGHT, BERRY_WIDTH, berryX[1], berryY[1]);
        ledMatrix_drawImage(BERRY_SPRITE, BERRY_HEIGHT, BERRY_WIDTH, berryX[0], berryY[0]);
        
        if (happyVisible)
            ledMatrix_drawImage(HAPPY_SPRITE, HAPPY_HEIGHT, HAPPY_WIDTH, 16, 0);

        if (frame < 8) { berryY[0] += 1; }

        if (frame < 2) { berryY[1] += 2; }
        if (frame < 3) { berryY[1] += 1; }
        
        if (frame < 6) { berryY[2] += 1; } // 3

        // take object & hop
        if (frame < 20) { dogIdleRight(5, frame, dogX, dogY); }
        else if (frame < 25) { dogWalkRight(8, frame, dogX, dogY); dogX += 1; }
        else if (frame < 35) { dogIdleRight(5, frame, dogX, dogY); }
        else if (frame < 40) { dogWalkRight(8, frame, dogX, dogY); dogX -= 1; }
        else if (frame < 43) { dogIdleRight(5, frame, dogX, dogY); }
        else if (frame < 48) { dogWalkRight(8, frame, dogX, dogY); dogX += 1; }
        else if (frame < 53) { dogIdleRight(5, frame, dogX, dogY); }
        else if (frame < 58) { dogWalkRight(8, frame, dogX, dogY); dogX -= 1; }
        else if (frame < 58+4) { dogIdleRight(5, frame, dogX, dogY); dogY -= 1; }
        else if (frame < 58+8) { dogIdleRight(5, frame, dogX, dogY); dogY += 1; }
        else { dogIdleRight(5, frame, dogX, dogY); happyVisible = true; }

        sleepForMs(frameTimeInMs);
    }
    ledMatrix_animateRightWipe(DEFAULT_WIPE_SPEED);
}
void animations_playSnackAnimation(int frameTimeInMs) {
    int dogX = 1;
    int dogY = 5;

    int berryX[1] = { 18 };
    int berryY[1] = { 1 };
    
    const int NUM_FRAMES = 28 * 2 + 12;
    for (int frame = 0; frame < NUM_FRAMES; frame++) {
        ledMatrix_fillScreen(BLACK);
        drawBackground();

        ledMatrix_drawImage(BERRY_SPRITE, BERRY_HEIGHT, BERRY_WIDTH, berryX[0], berryY[0]);

        if (frame < 8) { berryY[0] += 1; }

        // take object & hop
        if (frame < 20) { dogIdleRight(5, frame, dogX, dogY); }
        else if (frame < 25) { dogWalkRight(8, frame, dogX, dogY); dogX += 1; }
        else if (frame < 35) { dogIdleRight(5, frame, dogX, dogY); }
        else if (frame < 40) { dogWalkRight(8, frame, dogX, dogY); dogX -= 1; }
        else if (frame < 45) { dogIdleRight(5, frame, dogX, dogY); }
        else if (frame < 45+4) { dogIdleRight(5, frame, dogX, dogY); dogY -= 1; }
        else if (frame < 45+8) { dogIdleRight(5, frame, dogX, dogY); dogY += 1; }
        else { dogIdleRight(5, frame, dogX, dogY); }

        sleepForMs(frameTimeInMs);
    }
    ledMatrix_animateRightWipe(DEFAULT_WIPE_SPEED);
}
bool animations_playDrinkAnimation(int frameTimeInMs) {
    int dogX = 1;
    int dogY = 5;

    bool didSubmerge = false;
    const int WAIT_TIME = 28 * 5;
    for (int frame = 0; frame < WAIT_TIME; frame++) {
        ledMatrix_fillScreen(BLACK);
        drawBackground();
        dogIdleRight(5, frame, dogX, dogY);

        ledMatrix_drawHLine(RED, 0, 0, (frame * 32)/(28*5));
        
        if (waterSensor_isSubmerged()) {
            didSubmerge = true;
            break;
        }

        sleepForMs(frameTimeInMs);
    }

    if (didSubmerge) {
        // play actual drinking animation
        const int NUM_FRAMES = 28 * 2 + 14;
        for (int frame = 0; frame < NUM_FRAMES; frame++) {
            ledMatrix_fillScreen(BLACK);
            drawBackground();

            ledMatrix_drawRect(CYAN, 20, 0, 4, min((frame*14)/20, 14));

            if (frame < 20) { dogIdleRight(5, frame, dogX, dogY); }
            else if (frame < 25) { dogWalkRight(8, frame, dogX, dogY); dogX += 1; }
            else if (frame < 35) { dogIdleRight(5, frame, dogX, dogY); }
            else if (frame < 40) { dogWalkRight(8, frame, dogX, dogY); dogX -= 1; }
            else if (frame < 40+4) { dogIdleRight(5, frame, dogX, dogY); dogY -= 1; }
            else if (frame < 40+8) { dogIdleRight(5, frame, dogX, dogY); dogY += 1; }
            else { dogIdleRight(5, frame, dogX, dogY); }

            sleepForMs(frameTimeInMs);
        }
    } else {
        const int NUM_FRAMES = 16;
        for (int frame = 0; frame < NUM_FRAMES; frame++) {
            ledMatrix_fillScreen(BLACK);
            drawBackground();
            ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY);

            sleepForMs(frameTimeInMs);
        }
    }

    ledMatrix_animateRightWipe(DEFAULT_WIPE_SPEED);
    return didSubmerge;
}

void animations_playMoodAnimation(int frameTimeInMs, int mood) {
    int dogX = 1;
    int dogY = 5;

    bool faceVisible = false;
    int faceX = 15;
    int faceY = 6;
    
    const int NUM_FRAMES = 28 * 1 + 18;
    for (int frame = 0; frame < NUM_FRAMES; frame++) {
        ledMatrix_fillScreen(BLACK);
        drawBackground();

        if (faceVisible) {
            if (mood/10 <= 33) {
                ledMatrix_drawImage(SAD_SPRITE, SAD_WIDTH, SAD_HEIGHT, faceX, faceY);
            } else if (mood/10 <= 66) {
                ledMatrix_drawImage(BORED_SPRITE, BORED_WIDTH, BORED_HEIGHT, faceX, faceY);
            } else {
                ledMatrix_drawImage(HAPPY_SPRITE, HAPPY_WIDTH, HAPPY_HEIGHT, faceX, faceY);
            }
        }

        if (mood/10 <= 33) {
            ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY);
        } else if (mood/10 <= 66) {
            if (frame < 30) { ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY); }
            else if (frame < 30+4) { ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY); dogY -= 1; }
            else if (frame < 30+8) { ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY); dogY += 1; }
            else { ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY); }
        } else {
            if (frame < 30) { dogIdleRight(5, frame, dogX, dogY); }
            else if (frame < 30+4) { dogIdleRight(5, frame, dogX, dogY); dogY -= 1; }
            else if (frame < 30+8) { dogIdleRight(5, frame, dogX, dogY); dogY += 1; }
            else { dogIdleRight(5, frame, dogX, dogY); }
        }

        if (frame < 6) {  } 
        else if (frame < 7) { faceVisible = true; } 
        else if (frame < 14) { faceY -= 1;  } 
        else if (frame < 15) { } 
        else if (frame < 17) { faceY += 1; } 

        sleepForMs(frameTimeInMs);
    }
    ledMatrix_animateRightWipe(DEFAULT_WIPE_SPEED);
}
void animations_playFriendshipAnimation(int frameTimeInMs, int friendship) {
    int dogX = 1;
    int dogY = 5;

    bool heartVisible = false;
    int heartX = 15;
    int heartY = 10;
    
    const int NUM_FRAMES = 28 * 1 + 18;
    for (int frame = 0; frame < NUM_FRAMES; frame++) {
        ledMatrix_fillScreen(BLACK);
        drawBackground();

        if (heartVisible) {
            if (friendship/10 <= 33) {

            } else if (friendship/10 <= 66) {
                ledMatrix_drawImage(HEART_SMALL_SPRITE, HEART_SMALL_WIDTH, HEART_SMALL_HEIGHT, heartX, heartY);
            } else {
                ledMatrix_drawImage(HEART_SPRITE, HEART_WIDTH, HEART_HEIGHT, heartX, heartY);
                ledMatrix_drawImage(HEART_SPRITE, HEART_WIDTH, HEART_HEIGHT, heartX+6, heartY+1);
            }
        }

        if (friendship/10 <= 33) {
            ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY);
        } else if (friendship/10 <= 66) {
            if (frame < 30) { ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY); }
            else if (frame < 30+4) { ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY); dogY -= 1; }
            else if (frame < 30+8) { ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY); dogY += 1; }
            else { ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY); }
        } else {
            if (frame < 30) { dogIdleRight(5, frame, dogX, dogY); }
            else if (frame < 30+4) { dogIdleRight(5, frame, dogX, dogY); dogY -= 1; }
            else if (frame < 30+8) { dogIdleRight(5, frame, dogX, dogY); dogY += 1; }
            else { dogIdleRight(5, frame, dogX, dogY); }
        }

        if (frame < 6) {  } 
        else if (frame < 7) { heartVisible = true; } 
        else if (frame < 16) { heartY -= 1;  } 
        else if (frame < 17) { } 
        else if (frame < 19) { heartY += 1; } 

        sleepForMs(frameTimeInMs);
    }
    ledMatrix_animateRightWipe(DEFAULT_WIPE_SPEED);
}
void animations_playHungerAnimation(int frameTimeInMs, int hunger) {
    int dogX = 1;
    int dogY = 5;

    bool foodVisible = false;
    int foodX = 16;
    int foodY = 10;

    const int NUM_FRAMES = 28 * 1 + 18;
    for (int frame = 0; frame < NUM_FRAMES; frame++) {
        ledMatrix_fillScreen(BLACK);
        drawBackground();

        if (foodVisible) {
            if (hunger/10 <= 33) {
                ledMatrix_drawImage(SKULL_SPRITE, SKULL_WIDTH, SKULL_HEIGHT, foodX, foodY);
            } else if (hunger/10 <= 66) {
                ledMatrix_drawImage(MEAT_SPRITE, MEAT_WIDTH, MEAT_HEIGHT, foodX, foodY);
            } else {
                ledMatrix_drawImage(MEAT_SPRITE, MEAT_WIDTH, MEAT_HEIGHT, foodX-1, foodY-1);
                ledMatrix_drawImage(PLUS_SPRITE, PLUS_WIDTH, PLUS_HEIGHT, foodX+9, foodY);
                ledMatrix_drawImage(PLUS_SPRITE, PLUS_WIDTH, PLUS_HEIGHT, foodX+13, foodY);
            }
        }
        
        if (hunger/10 <= 33) {
            ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY);
        } else if (hunger/10 <= 66) {
            if (frame < 30) { ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY); }
            else if (frame < 30+4) { ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY); dogY -= 1; }
            else if (frame < 30+8) { ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY); dogY += 1; }
            else { ledMatrix_drawImage(DOG_FRAME_1_SAD, 15, 9, dogX, dogY); }
        } else {
            if (frame < 30) { dogIdleRight(5, frame, dogX, dogY); }
            else if (frame < 30+4) { dogIdleRight(5, frame, dogX, dogY); dogY -= 1; }
            else if (frame < 30+8) { dogIdleRight(5, frame, dogX, dogY); dogY += 1; }
            else { dogIdleRight(5, frame, dogX, dogY); }
        }

        if (frame < 6) {  } 
        else if (frame < 7) { foodVisible = true; } 
        else if (frame < 16) { foodY -= 1;  } 
        else if (frame < 17) { } 
        else if (frame < 19) { foodY += 1; } 

        sleepForMs(frameTimeInMs);
    }
    ledMatrix_animateRightWipe(DEFAULT_WIPE_SPEED);
}