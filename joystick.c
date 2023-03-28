#include <string.h>
#include <stdio.h>

#include "joystick.h"
#include "utils.h"

static char* valueFile = "/sys/class/gpio/gpio%d/value";

// Up, Down, Left, Right, Push
static int joystickGPIO[JOYSTICK_DIRECTION_COUNT] = {26, 46, 65, 47, 27};

void Joystick_init(void)
{
    // Configure pin's functions
    runCommand("config-pin p8.14 gpio");
    runCommand("config-pin p8.15 gpio");
    runCommand("config-pin p8.16 gpio");
    runCommand("config-pin p8.18 gpio");
    runCommand("config-pin p8.17 gpio");

    // Assume GPIO already exported

    // Configure pin to GPIO
    for (int i = 0; i < JOYSTICK_DIRECTION_COUNT; i++) {
        setGpioDirection(joystickGPIO[i], "in");
    }
}

void Joystick_cleanup(void)
{
    // do nothing
}

JoystickDirection Joystick_getDirection(void)
{
    for (int i = 0; i < JOYSTICK_DIRECTION_COUNT; i++) {
        char filePath[BUFSIZ];

        snprintf(filePath, BUFSIZ, valueFile, joystickGPIO[i]);
        int value = readIntFromFile(filePath);
        if (value == 0) {
            return i;
        }
    }
    return JOYSTICK_NO_DIRECTION;
}