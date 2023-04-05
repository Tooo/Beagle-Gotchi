// main.c
// Main Thread of Beagle gotchi
#include <stdio.h>
#include "../shutdown.h"
#include "../networking.h"
#include "../pet.h"
#include "../utils.h"

// Initialize/cleanup the module's data structures.
int main(void)
{
    Pet_init();
    udp_init();
    getchar();
    udp_clean_up();
    Pet_cleanup();


    return 0;
}
