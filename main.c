// main.c
// Main Thread of Beagle Gotchi
#include "shutdown.h"
#include "pet.h"
#include "petScreen.h"

// Initialize/cleanup the module's data structures.
static void main_init(void);
static void main_cleanup(void);

int main(void)
{
    main_init();
    Shutdown_wait();
    main_cleanup();
    return 0;
}

static void main_init(void)
{
    Pet_init();
    PetScreen_init();
}

int main_cleanup(void)
{
    PetScreen_cleanup();
    Pet_cleanup();
}