#include <stdio.h>

#include "../utils.h"
#include "../ledDisplay.h"


int main(void)
{
    Display_init();

    for (int i = 0; i < 100; i++) {
        Display_setDigit(i);
        sleepForMs(100);
    }
    
    Display_cleanup();
}