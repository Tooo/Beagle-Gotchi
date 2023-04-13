// pet.h
// Module for pets
// Has all the stats for each pet 
#ifndef PET_H_
#define PET_H_

#include <stdbool.h>

#define PET_NAME_MAX 30

// Start/stop Pet Thread
void Pet_init();
void Pet_cleanup();

// Create New Pet
void Pet_createPet(const char* name);

// Load/Unload Pet from file
void Pet_loadDefault();
void Pet_loadPet(const char* name);
void Pet_unloadPet();

// Name functions
void Pet_getName(char* buffer);
void Pet_setName(char* name);

// Age Function
int Pet_getAge();

typedef enum {
    Stage_EGG,         // 0-9
    Stage_BABY,        // 10-49
    Stage_CHILD,       // 50-100
    Stage_TEEN,        // 100-199
    Stage_ADULT,       // 200-
    STAGE_COUNT
} PetStage;
PetStage Pet_getStage();

// Mood Enum and Function
typedef enum {
    MOOD_VERY_UNHAPPY,  // 0-199
    MOOD_UNHAPPY,       // 200-399
    MOOD_NEUTRAL,       // 400-599
    MOOD_HAPPY,         // 600-799
    MOOD_VERY_HAPPY,    // 800-1000
    MOOD_COUNT
} PetMood;

PetMood Pet_getMood();
int Pet_getMoodNum();
void Pet_addMood(int value);

// Friendship Enum and Function
typedef enum {
    FRIEND_ACQUINTANCE,   // 0-199
    FRIEND_BUDDY,         // 200-399
    FRIEND_FRIEND,        // 400-599
    FRIEND_GOOD_FRIEND,   // 600-799
    FRIEND_BEST_FRIEND,   // 800-1000
    FRIEND_COUNT
} PetFriendship;

PetFriendship Pet_getFriendship();
int Pet_getFriendshipNum();
void Pet_addFriendship(int value);

// Hunger Enum and Functions
typedef enum {
    HUNGER_VERY_HUNGRY,   // 0-199
    HUNGER_HUNGRY,        // 200-399
    HUNGER_NEUTRAL,       // 400-599
    HUNGER_FULL,          // 600-799
    HUNGER_OVER_FULL,     // 800-1000
    HUNGER_COUNT
} PetHunger;

PetHunger Pet_getHunger();
int Pet_getHungerNum();
void Pet_addHunger(int value);

// Weight Functions
int Pet_getWeight();
void Pet_addWeight(int value);

#endif