// ledDisplay.h
// Module to manage LED Display
// Thread looping to set digits on display
#ifndef LED_DISPLAY_H_
#define LED_DISPLAY_H_

// Initialize/cleanup the module's data structures.
void Display_init(void);
void Display_cleanup(void);

// Set display digit variable, used in display thread
void Display_setDigit(int digit);

#endif