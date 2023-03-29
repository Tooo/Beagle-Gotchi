#include <pthread.h>
#include <stdbool.h>

#include "petScreen.h"
#include "terminal.h"
#include "utils.h"

#define PET_SCREEN_SLEEP_MS 1000
static void* petScreenThreadFunction(void* arg);
static pthread_t petScreenThread;
static bool stopping;

void PetScreen_init()
{
    pthread_create(&petScreenThread, NULL, petScreenThreadFunction, NULL);
    stopping = false;
}

void PetScreen_cleanup()
{
    stopping = true;
    pthread_join(petScreenThread, NULL);
}

static void* petScreenThreadFunction(void* arg)
{
    (void)arg;
    while (!stopping) {
        Terminal_printPet();
        printf("\n");
        Terminal_printPetStats();
        Terminal_printAdvancedPetStats();
        sleepForMs(PET_SCREEN_SLEEP_MS);
    }
    return NULL;
}