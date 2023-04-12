// joystick.h
// Module to manage the joystick
#ifndef JOYSTICK_H_
#define JOYSTICK_H_

typedef enum {
    JOYSTICK_UP = 0,
    JOYSTICK_DOWN,
    JOYSTICK_LEFT,
    JOYSTICK_RIGHT,
    JOYSTICK_PUSH,
    JOYSTICK_DIRECTION_COUNT,
    JOYSTICK_NO_DIRECTION
} JoystickDirection;

// Initialize/cleanup the module's data structures.
void Joystick_init(void);
void Joystick_cleanup(void);

// Get current direction of joystick
JoystickDirection Joystick_getDirection(void);

#endif