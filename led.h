// led.h
// Module to manage the Beaglebone leds
#ifndef LED_H_
#define LED_H_

typedef enum {
    LED0 = 0,
    LED1,
    LED2,
    LED3,
    LED_COUNT
} LedId;

// Initialize/cleanup the module's data structures.
void Led_init(void);
void Led_cleanup(void);

// Turn on/off leds
void Led_turnOn(LedId ledId);
void Led_turnOff(LedId ledId);
void Led_turnOffAll(void);

// Turn flash and unflash leds
void Led_flashAll(int hz);
void Led_unflashAll(void);

#endif