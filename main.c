// main.c
// Main Thread of Beagle Gotchi
#include "shutdown.h"
#include "pet.h"
#include "petMenu.h"
#include "led.h"
#include "zenLed.h"
#include "ledMatrix/ledMatrix.h"

#include "menuReader.h"

// Initialize/cleanup the module's data structures.
static void main_init(void);
static void main_cleanup(void);

int main(void)
{
    main_init();
    Shutdown_wait();
    main_cleanup();
    return 0;
}

static void main_init(void)
{
    ledMatrix_setup();
    ledMatrix_drawTestPage();
    MenuReader_allowTerminalIO(false);

    Pet_init();
    PetMenu_init();

    Led_init();
    ZenLed_init();
}

static void main_cleanup(void)
{
    ledMatrix_cleanup();
    ZenLed_cleanup();
    Led_cleanup();
    
    PetMenu_cleanup();
    Pet_cleanup();
}