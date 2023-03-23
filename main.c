// main.c
// Main Thread of Beagle Gotchi
#include <stdio.h>


#include "shutdown.h"
#include "menu.h"
#include "buttons.h"

// Initialize/cleanup the module's data structures.
// static void main_init(void);
// static void main_cleanup(void);
void print1(void);
void print2(void);
void print3(void);
void print4(void);



int main(void)
{
    Menu_init();
    Buttons_init();
    getchar();
    Buttons_cleanup();
    Menu_cleanup();

    return 0;
}
