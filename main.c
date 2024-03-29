// main.c
// Main Thread of Beagle Gotchi
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "utils/shutdown.h"
#include "pet/pet.h"
#include "pet/petMenu.h"
#include "hardware/led.h"
#include "hardware/zenLed.h"
#include "hardware/buzzer.h"
#include "ledMatrix/ledMatrix.h"
#include "hardware/audio.h"
#include "menu/menuReader.h"

#include "utils/networking.h"

#include "utils/utils.h"

// Initialize/cleanup the module's data structures.
static void main_init(int argc, char *argv[]);
static void main_cleanup(void);

// This function overrides the interrupt signal with our behaviour, then 
// continues with the original interrupt behaviour after.
struct sigaction oldAction;
void sigintHandler(int sigNo) 
{
    sigNo = sigNo;
    printf(" -> exiting gracefully...\n");
    
    // note: we may get some error messages if this is done before all the modules are
    // initialized, but it's better for the user experience if something like the led
    // matrix doesn't get leds stuck on.
    main_cleanup();
    
    sigaction(SIGINT, &oldAction, NULL);
    kill(0, SIGINT);
}

int main(int argc, char *argv[])
{
    // setup our custom interrupt handler for Ctrl+c
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = &sigintHandler;
    sigaction(SIGINT, &action, &oldAction);

    main_init(argc, argv);
    Shutdown_wait();
    main_cleanup();
    return 0;
}

static void main_init(int argc, char *argv[])
{
    // Running this program with the -t flag enables the debug terminal
    if ((argc > 1 && strcmp(argv[1], "-t") == 0) || 
        (argc > 2 && strcmp(argv[2], "-t") == 0)) {
        MenuReader_allowTerminalIO(true);
    }

    ledMatrix_setup();
    ledMatrix_drawIntroPage();
    sleepForMs(800);

    // running the program with the -d flag turns on debug mode 
    // (for setting current pet & restarting)
    if ((argc > 1 && strcmp(argv[1], "-d") == 0) || 
        (argc > 2 && strcmp(argv[2], "-d") == 0)) {
        setDebugMode(true);
    } else {
        setDebugMode(false);
    }

    Pet_init();

    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);

    PetMenu_init();

    Led_init();
    ZenLed_init();

    udp_init();
    
    Buzzer_init();
    Audio_init();
}

static void main_cleanup(void)
{
    ledMatrix_cleanup();
   
    Pet_cleanup();
    PetMenu_cleanup();
    
    ZenLed_cleanup();
    Led_cleanup();
    
    udp_clean_up();
    
    Buzzer_cleanup();
    Audio_cleanup();
    
    if (isFullShutdown()) {
        ledMatrix_cleanup_extra();
        runCommand("sudo shutdown -h now");
    }
}