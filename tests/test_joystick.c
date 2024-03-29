// test_joystick.c
// Test joystick on Zen Cape
// Prints current direction being pressed
// Push joystick to exit
#include <stdio.h>

#include "../utils/utils.h"
#include "../hardware/joystick.h"

int main(void)
{
    Joystick_init();

    JoystickDirection direction = JOYSTICK_NO_DIRECTION;

    while (direction != JOYSTICK_PUSH) {
        direction = Joystick_getDirection();

        switch(direction) {
            case JOYSTICK_UP:
                printf("UP\n");
                break;
            case JOYSTICK_DOWN:
                printf("DOWN\n");
                break;
            case JOYSTICK_LEFT:
                printf("LEFT\n");
                break;
            case JOYSTICK_RIGHT:
                printf("RIGHT\n");
                break;
            case JOYSTICK_PUSH:
                printf("EXIT\n");
                break;
            default:
                break;
        }
        sleepForMs(500);
    }
    

    Joystick_cleanup();
}