#include <stdio.h>

#include "../utils.h"
#include "../buzzer.h"

int main(void)
{
    Buzzer_init();

    Buzzer_play(3822256, 1911128, 1000);

    Buzzer_cleanup();
}