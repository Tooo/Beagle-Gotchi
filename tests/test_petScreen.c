#include "../pet.h"
#include "../petScreen.h"
#include "../utils.h"

static int sleepTimeMs = 10000;

int main(void)
{
    Pet_init();
    PetScreen_init();

    sleepForMs(sleepTimeMs);
    
    PetScreen_cleanup();
    Pet_cleanup();
    return 0;
}