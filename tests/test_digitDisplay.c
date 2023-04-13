#include <stdio.h>

#include "../utils/utils.h"
#include "../hardware/digitDisplay.h"


int main(void)
{
    DigitDisplay_init();

    for (int i = 0; i < 100; i++) {
        DigitDisplay_setDigit(i);
        sleepForMs(100);
    }
    
    DigitDisplay_cleanup();
}