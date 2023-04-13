// test_digitDisplay.c
// Test 2 digit display on Zen Cape
// Display number from 0 to 99
#include "../hardware/digitDisplay.h"
#include "../utils/utils.h"

int main(void)
{
    DigitDisplay_init();

    for (int i = 0; i < 100; i++) {
        DigitDisplay_setDigit(i);
        sleepForMs(100);
    }
    
    DigitDisplay_cleanup();
}