// test_audio.c
// Test for the playing audio.
// Plays Barking then Dog heavy breathing.
#include <stdio.h>

#include "../hardware/audio.h"
#include "../utils/utils.h"

// Sounds files used for test
static char* sounds[2] = {
    "beagle-gotchi-waves/mixkit-dog-barking-twice-1.wav",
    "beagle-gotchi-waves/mixkit-little-pug-dog-heavy-breathing-57.wav",
};

int main(void)
{
    Audio_init();

    Audio_playSoundWithThread(sounds[0]);
    Audio_joinThread();

    Audio_playSoundWithThread(sounds[1]);
    Audio_joinThread();

    Audio_cleanup();
}