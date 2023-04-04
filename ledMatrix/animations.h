// animations.h
// Stores all static animations

#ifndef ANIMATIONS_H
#define ANIMATIONS_H

extern const int DEFAULT_FRAME_SPEED;

void animations_playPettingAnimation(int frameTimeInMs);
void animations_playSlappingAnimation(int frameTimeInMs);

void animations_playMealAnimation(int frameTimeInMs);
void animations_playSnackAnimation(int frameTimeInMs);

void animations_playMoodAnimation(int frameTimeInMs);
void animations_playFriendshipAnimation(int frameTimeInMs);
void animations_playHungerAnimation(int frameTimeInMs);

#endif //!ANIMATIONS_H