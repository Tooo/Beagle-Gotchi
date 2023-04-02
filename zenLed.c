#include "zenLed.h"

#include "stdio.h"

#include "utils.h"

static char* periodFile = "/dev/bone/pwm/%s/period";
static char* enableFile = "/dev/bone/pwm/%s/enable";
static char* dutyCycleFile = "/dev/bone/pwm/%s/duty_cycle";

static const int ZEN_LED_PERIOD_TIME = 100000;

static char* zenLedValue[ZEN_LED_COUNT] = {"1/b", "2/a", "1/a"};

void ZenLed_init(void)
{
    runCommand("config-pin P9_14 pwm");
    runCommand("config-pin P9_16 pwm");
    runCommand("config-pin P8_19 pwm");

    for (int i = 0; i < ZEN_LED_COUNT; i++) {
        char command[MAX_BUFFER_SIZE];
        snprintf(command, MAX_BUFFER_SIZE, periodFile, zenLedValue[i]);
        writeIntToFile(command, ZEN_LED_PERIOD_TIME);
    }

    for (int i = 0; i < ZEN_LED_COUNT; i++) {
        char command[MAX_BUFFER_SIZE];
        snprintf(command, MAX_BUFFER_SIZE, enableFile, zenLedValue[i]);
        writeIntToFile(command, 1);
    }

    ZenLed_turnOffAll();
}

void ZenLed_cleanup(void)
{
    ZenLed_turnOffAll();
}

void ZenLed_turnOn(ZenLedId ledId)
{
    ZenLed_turnOffAll();
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, dutyCycleFile, zenLedValue[ledId]);
    writeIntToFile(command, ZEN_LED_PERIOD_TIME);
}

void ZenLed_turnOff(ZenLedId ledId)
{
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, dutyCycleFile, zenLedValue[ledId]);
    writeIntToFile(command, 0);   
}

void ZenLed_turnOffAll(void)
{
    for (int i = 0; i < ZEN_LED_COUNT; i++) {
        ZenLed_turnOff(i);
    } 
}