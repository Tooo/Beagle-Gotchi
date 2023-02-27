// ledMatrix.h
// Provides common graphics functions for interfacing with the 16x32 RGB led matrix panel 
// This module is *heavily* inspired from the file `test_ledMatrix.c` from one of the guides
// (but has been improved to use a background polling thread + other small changes)

#ifndef LED_MATRIX_H
#define LED_MATRIX_H

// colours
extern const int BLACK;
extern const int RED;
extern const int GREEN;
extern const int YELLOW;
extern const int BLUE;
extern const int PURPLE;
extern const int CYAN;
extern const int WHITE;

void ledMatrix_clearScreen(int colour);
void ledMatrix_setPixel(int x, int y, int colour);
void ledMatrix_refresh();

void ledMatrix_setup();
void ledMatrix_enable();
void ledMatrix_disable();
void ledMatrix_cleanup();

#endif // !LED_MATRIX_H