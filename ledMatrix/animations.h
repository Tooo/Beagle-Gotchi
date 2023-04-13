// animations.h
// Module to play animations to the LED Matrix

#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <stdbool.h>

extern const int DEFAULT_FRAME_SPEED;
// Interaction animations 
void animations_playPettingAnimation(int frameTimeInMs);
void animations_playSlappingAnimation(int frameTimeInMs);
// Food Animations
void animations_playMealAnimation(int frameTimeInMs);
void animations_playSnackAnimation(int frameTimeInMs);
bool animations_playDrinkAnimation(int frameTimeInMs);
// Status Animations
void animations_playMoodAnimation(int frameTimeInMs, int mood);
void animations_playFriendshipAnimation(int frameTimeInMs, int friendship);
void animations_playHungerAnimation(int frameTimeInMs, int hunger);

#endif //!ANIMATIONS_H