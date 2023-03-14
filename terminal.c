#include <stdio.h>

#include "terminal.h"
#include "pet.h"

static char petArt[16][16] ={
    {' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' '},
    {' ', '1', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', ' ', ' '},
    {' ', ' ', '1', '1', '1', '1', '1', ' ', ' ', '1', '1', '1', '1', '1', ' ', ' '},
    {' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' '},
    {' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' '},
    {' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' '},
    {' ', '1', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', ' '},
    {' ', '1', ' ', '1', '1', ' ', '1', ' ', ' ', '1', '1', ' ', '1', ' ', '1', ' '},
    {' ', '1', ' ', '1', '1', ' ', '1', ' ', ' ', '1', '1', ' ', '1', ' ', '1', ' '},
    {' ', '1', ' ', '1', '1', '1', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', '1', ' '},
    {' ', ' ', '1', ' ', ' ', ' ', ' ', '1', '1', ' ', ' ', ' ', ' ', '1', ' ', ' '},
    {' ', ' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', '1', ' ', '1', ' ', ' ', ' ', ' ', '1', ' ', '1', ' ', ' ', ' '},
    {' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', '1', ' ', '1', '1', ' ', '1', ' ', ' ', ' ', ' ', ' '},
};

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
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            char pixel = petArt[i][j];
            if (pixel == '1') {
                printf("X");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

static void printSymbols(int num)
{
    for (int i = 0; i < num; i++) {
        printf("X");
    }
    for (int i = 0; i < 5-num; i++) {
        printf("O");
    }
}

void Terminal_printPetStats()
{
    printf("Mood: ");
    printSymbols(Pet_getMood());
    
    printf(" Hunger: ");
    printSymbols(Pet_getHunger());

    printf(" Friendship: ");
    printSymbols(Pet_getFriendship());

    printf("\n");
}

void Terminal_printAdvancedPetStats()
{
    char name[PET_NAME_MAX];
    Pet_getName(name);
    printf("Name: %s ", name);
    printf("Age: %d ", Pet_getAge());
    printf("Mood: %d ", Pet_getMoodNum());
    printf("Hunger: %d ", Pet_getHungerNum());

    printf("Friendship: %d ", Pet_getFriendshipNum());
    printf("Weight: %d\n", Pet_getWeight());
}