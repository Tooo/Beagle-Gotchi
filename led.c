#include "led.h"

#include "stdio.h"

#include "utils.h"

static char* brightnessFile = "/sys/class/leds/beaglebone:green:usr%d/brightness";
static char* triggerFile = "/sys/class/leds/beaglebone:green:usr%d/trigger";
static char* delayOnFile = "/sys/class/leds/beaglebone:green:usr%d/delay_on";
static char* delayOffFile = "/sys/class/leds/beaglebone:green:usr%d/delay_off";

static const int TIMER_WAIT_TIME_MS = 300;

void Led_init(void)
{
    Led_turnOffAll();
    // Set LED triggers to None
    Led_unflashAll();
}

void Led_cleanup(void)
{
    Led_turnOffAll();
}

void Led_turnOn(LedId ledId)
{
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, brightnessFile, ledId);
    writeIntToFile(command, 1);
}

void Led_turnOff(LedId ledId)
{
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, brightnessFile, ledId);
    writeIntToFile(command, 0);   
}

void Led_turnOffAll(void)
{
    for (int i = 0; i < LED_COUNT; i++) {
        Led_turnOff(i);
    } 
}

void Led_flashAll(int hz)
{
    for (int i = 0; i < LED_COUNT; i++) {
        char filePath[MAX_BUFFER_SIZE];
        snprintf(filePath, MAX_BUFFER_SIZE, triggerFile, i);
        writeBufferToFile(filePath, "timer");
    }

    int duration = 1000 / hz;
    char durationString[5];
    snprintf(durationString, 5, "%d", duration);
    sleepForMs(TIMER_WAIT_TIME_MS);

    for (int i = 0; i < LED_COUNT; i++) {
        char filePath[MAX_BUFFER_SIZE];
        snprintf(filePath, MAX_BUFFER_SIZE, delayOnFile, i);
        writeBufferToFile(filePath, durationString);
    }

    for (int i = 0; i < LED_COUNT; i++) {
        char filePath[MAX_BUFFER_SIZE];
        snprintf(filePath, MAX_BUFFER_SIZE, delayOffFile, i);
        writeBufferToFile(filePath, durationString);
    }

}

void Led_unflashAll(void)
{
    for (int i = 0; i < LED_COUNT; i++) {
        char filePath[MAX_BUFFER_SIZE];
        snprintf(filePath, MAX_BUFFER_SIZE, triggerFile, i);
        writeBufferToFile(filePath, "none");
    }
}