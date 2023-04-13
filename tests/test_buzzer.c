// test_buzzer.c
// Test buzzer on Zen Cape
// Play notes A to G on the buzzer
#include "../hardware/buzzer.h"
#include "../utils/utils.h"

int main(void)
{
    Buzzer_init();

    int noteTime = 500;

    Buzzer_playNote(BUZZER_NOTE_A, noteTime);
    Buzzer_playNote(BUZZER_NOTE_B, noteTime);
    Buzzer_playNote(BUZZER_NOTE_C, noteTime);
    Buzzer_playNote(BUZZER_NOTE_D, noteTime);
    Buzzer_playNote(BUZZER_NOTE_E, noteTime);
    Buzzer_playNote(BUZZER_NOTE_F, noteTime);
    Buzzer_playNote(BUZZER_NOTE_G, noteTime);

    Buzzer_cleanup();
}