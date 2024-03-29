#include "petInteract.h"
#include "pet.h"
#include "../hardware/audio.h"

#include "../ledMatrix/ledMatrix.h"
#include "../ledMatrix/animations.h"

// Sounds for Bark command 
static char* sounds[2] = {
    "beagle-gotchi-waves/mixkit-dog-barking-twice-1.wav",
    "beagle-gotchi-waves/mixkit-little-pug-dog-heavy-breathing-57.wav",
};

void PetInteract_feedSnack(void)
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);
    animations_playSnackAnimation(DEFAULT_FRAME_SPEED);

    Pet_addHunger(100);
    Pet_addMood(200);
    Pet_addWeight(5);
    Pet_addFriendship(10);
}

void PetInteract_feedMeal(void)
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);
    animations_playMealAnimation(DEFAULT_FRAME_SPEED);

    Pet_addHunger(200);
    Pet_addMood(100);
    Pet_addWeight(10);
    Pet_addFriendship(5);
}

void PetInteract_drink(void) {
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);
    bool success = animations_playDrinkAnimation(DEFAULT_FRAME_SPEED); // NOTE: this is an interactive animation 

    if (success) {
        Pet_addHunger(50);
        Pet_addMood(150);
        Pet_addWeight(2);
    }
}

void PetInteract_pet(void)
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);
    animations_playPettingAnimation(DEFAULT_FRAME_SPEED);
    
    Pet_addMood(50);
    Pet_addFriendship(25);
}

void PetInteract_slap(void)
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);
    animations_playSlappingAnimation(DEFAULT_FRAME_SPEED);

    Pet_addMood(-50);
    Pet_addFriendship(-40);
}

void PetInteract_bark(void)
{
    Audio_playSoundWithThread(sounds[0]);
    Audio_joinThread();
    Pet_addMood(15);
}