// test_stateSaver.c
// Test state saver
// Unloads pet module and load it back
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../utils/stateSaver.h"

typedef struct {
    char name[50];
    int age;
    bool isHappy;
} testpet_t;


int main(void)
{
    testpet_t pet;
    pet.age = 20;
    pet.isHappy = true;
    strncpy(pet.name, "test", 50);

    printf("Creating pet named %s, aged %d, happy %d\n", pet.name, pet.age, pet.isHappy);
    
    printf("Unloading pet to save\n");
    StateSaver_unloadModule("testState", &pet, sizeof(pet));

    testpet_t newPet;

    StateSaver_loadModule("testState", &newPet, sizeof(newPet));

    printf("Loaded new pet named %s, aged %d, happy %d\n", newPet.name, newPet.age, newPet.isHappy);

    return 0;
}