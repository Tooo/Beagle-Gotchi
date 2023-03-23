// main.c
// Main Thread of Beagle gotchi
#include <stdio.h>
#include "shutdown.h"
#include "menu.h"
#include "buttons.h"

// Initialize/cleanup the module's data structures.

int main(void)
{
    Menu_init();
    Buttons_init();
    getchar();
    Buttons_cleanup();
    Menu_cleanup();

    return 0;
}
