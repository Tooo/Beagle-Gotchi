#include <stdio.h>

#include "../utils.h"
#include "../led.h"


int main(void)
{
    Led_init();

    for (int i = 0; i < 4; i++) {
        Led_turnOn(i);
        sleepForMs(500);
        Led_turnOff(i);
    }

    Led_flashAll(5);
    sleepForMs(3000);
    Led_unflashAll();

    Led_cleanup();
}