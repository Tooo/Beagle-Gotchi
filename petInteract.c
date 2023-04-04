#include "petInteract.h"
#include "pet.h"

#include "ledMatrix/ledMatrix.h"
#include "ledMatrix/animations.h"

void PetInteract_feedSnack(void)
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);

    // TODO: play snack animation
    Pet_addHunger(100);
    Pet_addMood(200);
    Pet_addWeight(5);
}

void PetInteract_feedMeal(void)
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);

    // TODO: ditto
    Pet_addHunger(200);
    Pet_addMood(100);
    Pet_addWeight(10);
}

void PetInteract_pet(void)
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);
    animations_playPettingAnimation(DEFAULT_FRAME_SPEED);
    Pet_addMood(50);
}

void PetInteract_slap(void)
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);

    // TODO: ditto
    Pet_addMood(-50);
}