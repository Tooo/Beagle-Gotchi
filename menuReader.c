#include <pthread.h>
#include <stdatomic.h>

#include "menuReader.h"
#include "menu.h"
#include "utils.h"
#include "joystick.h"
#include "led.h"
#include "buzzer.h"

#include "networking.h"

static const int joystickSleepMs = 100;
static const int joystickPushSleepMS = 250;
static const int joystickDirectionSleepMS = 200;

static int ledCurrent = 0;

// Menu Reader Thread
static void* menuReaderThreadFunction(void* arg);
static pthread_t menuReaderThread;

static bool stopping;
atomic_bool terminalIODisabled = true; // if true, all printing from this thread will be disabled (debugging reasons)
//pthread_mutex_t ledMatrix;
// pthread_mutex_lock()

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
    if (!terminalIODisabled) {
        Menu_printOptions();
    }

    ledMenu();

	if (!udp_usingLEDMatrix()) {
        Menu_renderMenu();
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
            Buzzer_playNote(BUZZER_NOTE_C, 60);
            Buzzer_playNote(BUZZER_NOTE_D, 60);
            Buzzer_playNote(BUZZER_NOTE_E, 60);
            Menu_selectOption();
            sleepForMs(joystickPushSleepMS-60*3);
        } else {
            Buzzer_playNote(BUZZER_NOTE_A, 100);
            Menu_moveHighlighted(direction);
            sleepForMs(joystickDirectionSleepMS-100);
        }
    }
    return NULL;
}