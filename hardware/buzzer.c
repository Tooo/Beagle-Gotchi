#include "buzzer.h"
#include "../utils/utils.h"
#include <stdio.h>

static char* periodFile = "/dev/bone/pwm/0/a/period";
static char* dutyCycleFile = "/dev/bone/pwm/0/a/duty_cycle";
static char* enableFile = "/dev/bone/pwm/0/a/enable";

// Obtain values in pages.mtu.edu/~suits/notefreqs.html
static double notes[BUZZER_NOTE_COUNT] = {220, 246.94, 261.63, 293.66, 329.63, 349.23, 392};

void Buzzer_init(void)
{
    runCommand("config-pin P9_22 pwm");
}

void Buzzer_cleanup(void)
{
    // To confirm the buzzer is not playing
    writeIntToFile(enableFile, 0);
}

void Buzzer_play(int period, int dutyCycle, int timeInMs)
{
    writeIntToFile(periodFile, period);
    writeIntToFile(dutyCycleFile, dutyCycle);
    writeIntToFile(enableFile, 1);

    sleepForMs(timeInMs);

    writeIntToFile(enableFile, 0);
}

void Buzzer_playNote(BuzzerNoteId noteId, int timeInMs)
{
    int nsPerS = 1000000000;
    double hz = notes[noteId];
    int period = nsPerS*(1/hz);
    int dutyCycle = period/2;

    Buzzer_play(period, dutyCycle, timeInMs);
}