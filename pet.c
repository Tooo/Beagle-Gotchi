#include <pthread.h>
#include <string.h>

#include "pet.h"
#include "utils.h"
#include "terminal.h"
#include "stateSaver.h"
#include "shutdown.h"

typedef struct {
    char name[PET_NAME_MAX];
    int age;

    int mood;
    int friendship;

    int hunger;
    int weight;
} pet_t;

static pet_t pet;

static char* petFileHeader = "pet_%s";

#define PET_SLEEP_MS 1000

static void* petThreadFunction(void* arg);
static pthread_t petThread;
static bool stopping;

void Pet_createPet(char* name)
{
    strncpy(pet.name, name, PET_NAME_MAX);
    pet.age = 0;
    pet.mood = 500;
    pet.friendship = 0;
    pet.hunger = 500;
    pet.weight = 10;
}

void Pet_init()
{
    char name[PET_NAME_MAX];
    Terminal_inputPetName(name);

    char fileName[FILENAME_MAX];
    snprintf(fileName, FILENAME_MAX, petFileHeader, name);

    if (StateSaver_stateExist(fileName)) {
        Terminal_printLoadedPetMsg(name);
        Pet_loadPet(name);
    } else {
        Terminal_printNewPetMsg(name);
        Pet_createPet(name);
    }

    pthread_create(&petThread, NULL, petThreadFunction, NULL);
    stopping = false;
}

void Pet_cleanup()
{
    stopping = true;
    pthread_join(petThread, NULL);
    Pet_unloadPet();
}

void Pet_loadPet(char* name)
{
    char fileName[PET_NAME_MAX];
    snprintf(fileName, PET_NAME_MAX, petFileHeader, name);

    StateSaver_loadModule(fileName, &pet, sizeof(pet));
}

void Pet_unloadPet()
{
    char fileName[FILENAME_MAX];
    snprintf(fileName, PET_NAME_MAX, petFileHeader, pet.name);

    StateSaver_unloadModule(fileName, &pet, sizeof(pet));
}

void Pet_getName(char* buffer)
{
    strncpy(buffer, pet.name, PET_NAME_MAX);
}

void Pet_setName(char* name)
{
    strncpy(pet.name, name, PET_NAME_MAX);
}

int Pet_getAge()
{
    return pet.age;
}

PetMood Pet_getMood()
{
    return pet.mood / 200;
}

int Pet_getMoodNum()
{
    return pet.mood;
}

void Pet_addMood(int value)
{
    pet.mood += value;
    if (pet.mood < 0) {
        pet.mood = 0;
    }   else if (pet.mood > 1000) {
        pet.mood = 1000;
    }
}

PetFriendship Pet_getFriendship()
{
    return pet.friendship / 200;
}

int Pet_getFriendshipNum()
{
    return pet.friendship;
}

void Pet_addFriendship(int value)
{
    pet.friendship += value;
    if (pet.friendship < 0) {
        pet.friendship = 0;
    }   else if (pet.friendship > 1000) {
        pet.friendship = 1000;
    }
}

PetHunger Pet_getHunger()
{
    return pet.hunger / 200;
}

int Pet_getHungerNum()
{
    return pet.hunger;
}

void Pet_addHunger(int value)
{
    pet.hunger += value;
    if (pet.hunger < 0) {
        pet.hunger = 0;
    }   else if (pet.hunger > 1000) {
        pet.hunger = 1000;
    }
}

int Pet_getWeight()
{
    return pet.weight;
}

void Pet_addWeight(int value)
{
    pet.weight += value;
}

static void* petThreadFunction(void* arg)
{
    (void)arg;
    for (int i = 0; i < 5; i++) {
    // while (!stopping) {
        if (pet.hunger > 0) {
            pet.hunger--;
        }

        if (pet.mood > 0) {
            pet.mood--;
        }

        pet.age++;
        sleepForMs(PET_SLEEP_MS);
    }
    Shutdown_trigger();
    return NULL;
}