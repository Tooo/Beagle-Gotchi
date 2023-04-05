#include <stdio.h>

#include "../utils.h"
#include "../audio.h"

static char* sounds[3] = {
    "beagle-gotchi-waves/mixkit-dog-barking-twice-1.wav",
    "beagle-gotchi-waves/mixkit-little-pug-dog-heavy-breathing-57.wav",
};

int main(void)
{
    Audio_init();

    Audio_playSound(sounds[1]);
    Audio_playSound(sounds[0]);
    Audio_playSound(sounds[0]);
    Audio_playSound(sounds[0]);
    Audio_playSound(sounds[0]);
    Audio_cleanup();
}