#include <pthread.h>
#include <sched.h>
#include <stdatomic.h>

#include "menuReader.h"
#include "menu.h"
#include "utils.h"
#include "joystick.h"
#include "led.h"

#include "ledMatrix/ledMatrix.h" // for colours

static const int joystickSleepMs = 100;
static const int joystickPushSleepMS = 250;
static const int joystickDirectionSleepMS = 200;

static int ledCurrent = 0;

// Menu Reader Thread
static void* menuReaderThreadFunction(void* arg);
static pthread_t menuReaderThread;

static bool stopping;
atomic_bool terminalIODisabled = false; // if true, all printing from this thread will be disabled (debugging reasons)

void MenuReader_allowTerminalIO(bool enabled) {
    terminalIODisabled = !enabled;
}

void MenuReader_init(void)
{
    stopping = false;
    ledCurrent = -1;
    pthread_create(&menuReaderThread, NULL, menuReaderThreadFunction, NULL);
}

void MenuReader_cleanup(void)
{
    Led_turnOffAll();
    stopping = true;
    pthread_join(menuReaderThread, NULL);
}

void ledMenu(void)
{
    int higlighted = Menu_getCurrentHiglighted();

    // No change in selection
    if (higlighted == ledCurrent) {
        return;
    }

    Led_turnOffAll();

    if (higlighted < LED_COUNT) {
        Led_turnOn(higlighted);
        return;
    }

    Led_turnOn(3);
    higlighted -= LED_COUNT;
    if (higlighted < LED_COUNT) {
        Led_turnOn(higlighted);
        return;
    }
}

// update 
void updateMenu() {
    if (!terminalIODisabled)
        Menu_printOptions();

    ledMenu();

    // TODO: Move this into a function in Menu_
    ledMatrix_fillScreen(BLACK);
    for (int i = 0; i < 4; i++) {
        if (Menu_getCurrentHiglighted()+i >= Menu_getMenuSize()) 
            continue;

        const char* curr = Menu_getMenuName(Menu_getCurrentHiglighted()+i);
        if (Menu_getCurrentHiglighted()+i == Menu_getCurrentHiglighted()) {
            ledMatrix_drawString(curr, 0, i * 4, GREEN); // YELLOW
        } else {
            ledMatrix_drawString(curr, 0, i * 4, WHITE);
        }
    }
}

void* menuReaderThreadFunction(void* arg)
{
    (void)arg;

    while(!stopping) {
        updateMenu();
        JoystickDirection direction = Joystick_getDirection();

        if (direction == JOYSTICK_NO_DIRECTION) {
            sleepForMs(joystickSleepMs);
        } else if (direction == JOYSTICK_PUSH) {
            Menu_selectOption();
            sleepForMs(joystickPushSleepMS);
        } else {
            Menu_moveHighlighted(direction);
            sleepForMs(joystickDirectionSleepMS);
        }
    }
    return NULL;
}