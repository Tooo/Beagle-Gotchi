// pet.h
// Module to interact with pets
// User available interactions with the pet 
// Plays the animation and alters pet stats
#ifndef PET_INTERACT_H_
#define PET_INTERACT_H_

// Food related interations
void PetInteract_feedSnack(void);
void PetInteract_feedMeal(void);
void PetInteract_drink(void);

// Pet actions interactions 
void PetInteract_pet(void);
void PetInteract_slap(void);

// Plays a sound from the pet 
void PetInteract_bark(void);

#endif