// main.c
// Main Thread of Beagle Gotchi
#include <stdio.h>
#include <string.h>

#include "shutdown.h"
#include "pet.h"
#include "petMenu.h"
#include "led.h"
#include "zenLed.h"
#include "ledMatrix/ledMatrix.h"

#include "menuReader.h"

#include "networking.h"

#include "utils.h"

// Initialize/cleanup the module's data structures.
static void main_init(int argc, char *argv[]);
static void main_cleanup(void);

int main(int argc, char *argv[])
{
    main_init(argc, argv);
    Shutdown_wait();
    main_cleanup();
    return 0;
}

static void main_init(int argc, char *argv[])
{
    // Running this program with the -t flag enables the debug terminal
    if (argc > 1 && strcmp(argv[1], "-t") == 0) {
        MenuReader_allowTerminalIO(true);
    }

    ledMatrix_setup();
    ledMatrix_drawIntroPage();
    sleepForMs(100);

    Pet_init();

    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED * 2);

    PetMenu_init();

    Led_init();
    ZenLed_init();

    udp_init();
    
}

static void main_cleanup(void)
{
    ledMatrix_cleanup();
    ZenLed_cleanup();
    Led_cleanup();
    
    PetMenu_cleanup();
    Pet_cleanup();
    udp_clean_up();
}