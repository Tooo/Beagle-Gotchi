#include <stdio.h>

#include "../utils.h"
#include "../audio.h"

#define SOURCE_FILE "wave-files/100060__menegass__gui-drum-splash-hard.wav"

int main(void)
{
    Audio_init();

    Audio_playSound(SOURCE_FILE);

    Audio_cleanup();
}