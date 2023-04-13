// test_petScreen.c
// Test for pet and pet screen
// Displays life cycle of pet with terminal view
#include "../pet/pet.h"
#include "../pet/petScreen.h"
#include "../utils/utils.h"

static int sleepTimeMs = 10000;

int main(void)
{
    Pet_init(true);
    PetScreen_init();

    sleepForMs(sleepTimeMs);
    
    PetScreen_cleanup();
    Pet_cleanup();
    return 0;
}