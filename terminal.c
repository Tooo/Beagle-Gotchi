#include <stdio.h>

#include "terminal.h"
#include "pet.h"

void Terminal_inputPetName(char* name)
{
    printf("Input Pet Name: ");
    scanf("%s", name);
}

void Terminal_printNewPetMsg(char* name)
{
    printf("Creating new Pet named: %s\n", name);
}

void Terminal_printLoadedPetMsg(char* name)
{
    printf("Loading existing Pet named: %s\n", name);
}

void Terminal_printPet()
{

}

void Terminal_printPetStats()
{
    char name[PET_NAME_MAX];
    Pet_getName(name);
    printf("Name: %s ", name);
    printf("Age: %d ", Pet_getAge());
    printf("Mood: %d ", Pet_getMoodNum());
    printf("Friendship: %d ", Pet_getFriendshipNum());
    printf("Hunger: %d ", Pet_getHungerNum());
    printf("Weight: %d\n", Pet_getWeight());
}