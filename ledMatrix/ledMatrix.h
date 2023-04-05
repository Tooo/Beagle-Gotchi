// ledMatrix.h
// Provides common graphics functions for interfacing with the 16x32 RGB led matrix panel 
// This module is *heavily* inspired from the file `test_ledMatrix.c` from one of the guides
// (but has been improved to use a background polling thread + other small changes)

#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <stdbool.h>
#include <pthread.h>

// colours
extern const int BLACK;
extern const int RED;
extern const int GREEN;
extern const int YELLOW;
extern const int BLUE;
extern const int PURPLE;
extern const int CYAN;
extern const int WHITE;

extern const int DEFAULT_WIPE_SPEED;

void ledMatrix_animateLeftWipe(int rateInMs); // this function sleeps the current thread to run the animation
void ledMatrix_animateRightWipe(int rateInMs);

void ledMatrix_drawIntroPage();
void ledMatrix_drawExitPage();

// drawing functions
void ledMatrix_fillScreen(int colour);
void ledMatrix_drawImage(const int* colorData, int width, int height, int xoff, int yoff);
void ledMatrix_drawImageHFlipped(const int* colorData, int width, int height, int xoff, int yoff);
void ledMatrix_drawHLine(int color, int xpoint, int ypoint, int xlength);
void ledMatrix_drawVLine(int color, int xpoint, int ypoint, int ylength);
void ledMatrix_drawRect(int color, int xpoint, int ypoint, int xlength, int ylength);
void ledMatrix_drawString(const char* text, int xpoint, int ypoint, int color);

void ledMatrix_setPixel(int color, int x, int y);
void ledMatrix_refresh();

void ledMatrix_setup();
void ledMatrix_cleanup_extra();
void ledMatrix_cleanup();

void ledMatrix_toString(char* outstr, bool visibility_mode);

#endif // !LED_MATRIX_H