// main.c
// Main Thread of Beagle gotchi
#include <stdio.h>
#include "../shutdown.h"
#include "../networking.h"

// Initialize/cleanup the module's data structures.

int main(void)
{
    init_udp_listen();
    getchar();
    udp_clean_up();


    return 0;
}
