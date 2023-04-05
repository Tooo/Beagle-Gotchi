// animations.h
// Stores all static animations

#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <stdbool.h>

extern const int DEFAULT_FRAME_SPEED;

void animations_playPettingAnimation(int frameTimeInMs);
void animations_playSlappingAnimation(int frameTimeInMs);

void animations_playMealAnimation(int frameTimeInMs);
void animations_playSnackAnimation(int frameTimeInMs);
bool animations_playDrinkAnimation(int frameTimeInMs);

void animations_playMoodAnimation(int frameTimeInMs, int mood);
void animations_playFriendshipAnimation(int frameTimeInMs, int friendship);
void animations_playHungerAnimation(int frameTimeInMs, int hunger);

#endif //!ANIMATIONS_H