// pet.h
#ifndef PET_H_
#define PET_H_

#include <stdbool.h>

#define PET_NAME_MAX 30

void Pet_startPet();
void Pet_stopPet();

void Pet_createPet(char* name);
void Pet_loadPet(char* name);
void Pet_unloadPet();

void Pet_getName(char* buffer);
void Pet_setName(char* name);

int Pet_getAge();

typedef enum {
    MOOD_VERY_UNHAPPY,
    MOOD_UNHAPPY,
    MOOD_NEUTRAL,
    MOOD_HAPPY,
    MOOD_VERY_HAPPY
} PetMood;

PetMood Pet_getMood();
void Pet_addMood(int value);

typedef enum {
    FRIEND_ACQUINTANCE,
    FRIEND_BUDDY,
    FRIEND_FRIEND,
    FRIEND_GOOD_FRIEND,
    FRIEND_BEST_FRIEND
} PetFriendship;

PetFriendship Pet_getFriendship();
void Pet_addFriendship(int value);

typedef enum {
    HUNGER_VERY_HUNGRY,
    HUNGER_HUNGRY,
    HUNGER_NEUTRAL,
    HUNGER_FULL,
    HUNGER_OVER_FULL
} PetHunger;

PetHunger Pet_getHunger();
void Pet_addHunger(int value);

int Pet_getWeight();
void Pet_addWeight(int value);

#endif