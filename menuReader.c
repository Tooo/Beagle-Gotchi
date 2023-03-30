#include <pthread.h>
#include <stdbool.h>

#include "menuReader.h"
#include "menu.h"
#include "utils.h"
#include "joystick.h"

static const int joystickSleepMs = 10;
static const int joystickPushSleepMS = 250;
static const int joystickDirectionSleepMS = 200;

// Menu Reader Thread
static void* menuReaderThreadFunction(void* arg);
static pthread_t menuReaderThread;

static bool stopping;

void MenuReader_init(void)
{
    stopping = false;
    pthread_create(&menuReaderThread, NULL, menuReaderThreadFunction, NULL);
}

void MenuReader_cleanup(void)
{
    stopping = true;
    pthread_join(menuReaderThread, NULL);
}

void* menuReaderThreadFunction(void* arg)
{
    (void)arg;
    while(!stopping) {
        Menu_printOptions();
        JoystickDirection direction = Joystick_getDirection();

        if (direction == JOYSTICK_NO_DIRECTION) {
            sleepForMs(joystickSleepMs);
            continue;
        }

        if (direction == JOYSTICK_PUSH) {
            Menu_selectOption();
            Menu_printOptions();
            sleepForMs(joystickPushSleepMS);
            continue;
        }

        Menu_moveHighlighted(direction);
        Menu_printOptions();

        sleepForMs(joystickDirectionSleepMS);
    }
    return NULL;
}