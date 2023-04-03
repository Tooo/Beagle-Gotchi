#include "petInteract.h"
#include "pet.h"

void PetInteract_feedSnack(void)
{
    Pet_addHunger(100);
    Pet_addMood(200);
    Pet_addWeight(5);
}

void PetInteract_feedMeal(void)
{
    Pet_addHunger(200);
    Pet_addMood(100);
    Pet_addWeight(10);
}

void PetInteract_pet(void)
{
    Pet_addMood(50);
}

void PetInteract_slap(void)
{
    Pet_addMood(-50);
}