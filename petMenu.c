#include <stdio.h>

#include "menu.h"
#include "menuReader.h"
#include "pet.h"
#include "petInteract.h"
#include "shutdown.h"
#include "digitDisplay.h"
#include "zenLed.h"

#include "utils.h"
#include "ledMatrix/ledMatrix.h"
#include "ledMatrix/animations.h"

typedef enum {
    PET_MENU_MAIN = 0,
    PET_MENU_INTERACT,
    PET_MENU_PLAY,
    PET_MENU_FOOD,
    PET_MENU_STATUS,
    PET_MENU_COUNT
} PetMenuOptions;

static void printOption(void)
{
    Menu_clickedPrint();
}

// Main Menu Functions
static void goToInteract(void)
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);

    Menu_changeMenu(PET_MENU_INTERACT);
    Menu_moveCursorToTop();
}

static void goToPlay(void) 
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);

    Menu_changeMenu(PET_MENU_PLAY);
    Menu_moveCursorToTop();
}

static void goToFood(void) 
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);

    Menu_changeMenu(PET_MENU_FOOD);
    Menu_moveCursorToTop();
}

static void goToStatus(void)
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);
    DigitDisplay_init();

    Menu_changeMenu(PET_MENU_STATUS);
    Menu_moveCursorToTop();
}

static void quit(void)
{
    ledMatrix_animateRightWipe(DEFAULT_WIPE_SPEED);
    ledMatrix_drawExitPage();
    sleepForMs(800);
    
    ledMatrix_animateRightWipe(DEFAULT_WIPE_SPEED);
    if (isDebugMode()) {
        setFullShutdown(false);
    } else {
        setFullShutdown(true);
    }
    Shutdown_trigger();
}

static void empty(void) { }

static void newPet(void) {
    // this forces the user to pick a new pet next time -> if same name as before, will load the pet
    remove("beagle-gotchi-states/meta.txt");
    sleepForMs(100);
    
    ledMatrix_animateRightWipe(DEFAULT_WIPE_SPEED);
    setFullShutdown(false);
    Shutdown_trigger();
}

static void returnToMain(void)
{
    ledMatrix_animateRightWipe(DEFAULT_WIPE_SPEED);

    Menu_changeMenu(0);
}

static void moodOption(void)
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);

    int mood = Pet_getMoodNum();
    ZenLed_turnOn(ZEN_LED_BLUE);
    DigitDisplay_setDigit(mood/10);

    animations_playMoodAnimation(DEFAULT_FRAME_SPEED, mood);
}

static void friendshipOption(void)
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);

    int friendship = Pet_getFriendshipNum();
    ZenLed_turnOn(ZEN_LED_RED);
    DigitDisplay_setDigit(friendship/10);

    animations_playFriendshipAnimation(DEFAULT_FRAME_SPEED, friendship);
}

static void hungerOption(void)
{
    ledMatrix_animateLeftWipe(DEFAULT_WIPE_SPEED);
    int hunger = Pet_getHungerNum();
    ZenLed_turnOn(ZEN_LED_GREEN);
    DigitDisplay_setDigit(hunger/10);

    animations_playHungerAnimation(DEFAULT_FRAME_SPEED);
}

static void returnToMainDigit(void)
{
    ledMatrix_animateRightWipe(DEFAULT_WIPE_SPEED);
    ZenLed_turnOffAll();
    DigitDisplay_cleanup();

    Menu_changeMenu(0);
}

// Menu Names and Functions
static char *mainNames[] = {"Interact", "Play", "Food", "Status", "Quit", " ", "New Pet"};
static void (*mainFuncs[MAX_MENU_FUNC_COUNT])(void) = {&goToInteract, &goToPlay, &goToFood, &goToStatus, &quit, &empty, &newPet};

static char *interactNames[] = {"Pet", "Slap", "Go Back"};
static void (*interactFuncs[MAX_MENU_FUNC_COUNT])(void) = {&PetInteract_pet, &PetInteract_slap, &returnToMain};

static char *gamesNames[] = {"A", "B", "C", "Go Back"};
static void (*gamesFuncs[MAX_MENU_FUNC_COUNT])(void) = {&printOption, &printOption, &printOption, &returnToMain};

static char *feedNames[] = {"Meal", "Snack", "Drink", "Go Back"};
static void (*feedFuncs[MAX_MENU_FUNC_COUNT])(void) = {&PetInteract_feedMeal, &PetInteract_feedSnack, &PetInteract_drink, &returnToMain};

// mood, friendship, hunger
static char *statusNames[] = {"Mood", "Friend", "Food", "Go Back"};
static void (*statusFuncs[MAX_MENU_FUNC_COUNT])(void) = {&moodOption, &friendshipOption, &hungerOption, &returnToMainDigit};

void PetMenu_init()
{    
    MenuOptions_insert(mainNames, mainFuncs, 7);
    MenuOptions_insert(interactNames, interactFuncs, 3);
    MenuOptions_insert(gamesNames, gamesFuncs, 4);
    MenuOptions_insert(feedNames, feedFuncs, 4);
    MenuOptions_insert(statusNames, statusFuncs, 4);

    Menu_init();
    MenuReader_init();
}

void PetMenu_cleanup()
{
    MenuReader_cleanup();
    Menu_cleanup();
}
