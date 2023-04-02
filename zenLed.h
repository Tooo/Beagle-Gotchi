// led.h
// Module to manage the Beaglebone leds
#ifndef LED_H_
#define LED_H_

typedef enum {
    ZEN_LED_RED = 0,
    ZEN_LED_GREEN,
    ZEN_LED_BLUE,
    ZEN_LED_COUNT
} ZenLedId;

// Initialize/cleanup the module's data structures.
void ZenLed_init(void);
void ZenLed_cleanup(void);

// Turn on/off leds
void ZenLed_turnOn(ZenLedId ledId);
void ZenLed_turnOff(ZenLedId ledId);
void ZenLed_turnOffAll(void);

#endif