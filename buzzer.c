#include "buzzer.h"
#include "utils.h"

static char* periodFile = "/dev/bone/pwm/0/a/period";
static char* dutyCycleFile = "/dev/bone/pwm/0/a/duty_cycle";
static char* enableFile = "/dev/bone/pwm/0/a/enable";

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