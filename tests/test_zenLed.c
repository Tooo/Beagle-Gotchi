#include "../hardware/zenLed.h"
#include "../utils/utils.h"

int main(void)
{
    ZenLed_init();

    for (int i = 0; i < ZEN_LED_COUNT; i++) {
        ZenLed_turnOn(i);
        sleepForMs(1000);
    }

    ZenLed_cleanup();
}