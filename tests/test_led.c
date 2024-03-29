// test_led.c
// Test LEDs on Beagle Bone
// Lights each LED and flash LED
#include "../hardware/led.h"
#include "../utils/utils.h"

int main(void)
{
    Led_init();

    for (int i = 0; i < LED_COUNT; i++) {
        Led_turnOn(i);
        sleepForMs(500);
        Led_turnOff(i);
    }

    Led_flashAll(5);
    sleepForMs(3000);
    Led_unflashAll();

    Led_cleanup();
}