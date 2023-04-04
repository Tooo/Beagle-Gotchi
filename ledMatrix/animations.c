#include "animations.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "../utils.h"
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

    const int NUM_FRAMES = 28 * 4 + 3;
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

        if (frame < 5) {

        } else if (frame < 12) {
            handX -= 1;
        } else if (frame < 12 + 16 * 3) {
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