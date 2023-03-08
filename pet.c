#include <pthread.h>
#include <string.h>

#include "pet.h"
#include "utils.h"

typedef struct {
    char name[PET_NAME_MAX];
    int age;

    int mood;
    int friendship;

    int hunger;
    int weight;
} pet_t;

static void* petThreadFunction(void* arg);
static pthread_t petThread;
static bool stopping;

static pet_t pet;

void Pet_createPet(char* name)
{
    strncpy(pet.name, name, PET_NAME_MAX);
    pet.age = 0;
    pet.mood = 500;
    pet.friendship = 0;
    pet.hunger = 500;
    pet.weight = 10;
}

// void Pet_loadPet(char* name)
// {

// }

// void Pet_unloadPet()
// {

// }

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

void Pet_startPet()
{
    pthread_create(&petThread, NULL, petThreadFunction, NULL);
    stopping = false;
}

void Pet_stopPet()
{
    pthread_join(petThread, NULL);
    stopping = true;
}

static void* petThreadFunction(void* arg)
{
    (void)arg;
    while (!stopping) {
        sleepForMs(1000);
    }
    return NULL;
}