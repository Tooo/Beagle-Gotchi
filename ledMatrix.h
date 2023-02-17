// ledMatrix.h
// Provices common graphics functions for interfacing with the 16x32 RGB led matrix panel 
#ifndef LED_MATRIX_H
#define LED_MATRIX_H

void ledMatrix_setup();
void ledMatrix_enable();
void ledMatrix_disable();
void ledMatrix_cleanup();

#endif // !LED_MATRIX_H