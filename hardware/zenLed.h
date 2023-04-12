// zenLed.h
// Module to manage the Zencape leds
#ifndef ZEN_LED_H_
#define ZEN_LED_H_

typedef enum {
    ZEN_LED_RED = 0,
    ZEN_LED_GREEN,
    ZEN_LED_BLUE,
    ZEN_LED_COUNT
} ZenLedId;

// Initialize/cleanup the module's data structures.
void ZenLed_init(void);
void ZenLed_cleanup(void);

// Turn on/off zen leds
void ZenLed_turnOn(ZenLedId ledId);
void ZenLed_turnOff(ZenLedId ledId);
void ZenLed_turnOffAll(void);

#endif