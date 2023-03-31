#include <stdio.h>

#include "menu.h"
#include "menuReader.h"
#include "pet.h"
#include "petInteract.h"
#include "shutdown.h"
#include "digitDisplay.h"

typedef enum {
    PET_MENU_MAIN = 0,
    PET_MENU_INTERACT,
    PET_MENU_GAMES,
    PET_MENU_FEED,
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
    Menu_changeMenu(PET_MENU_INTERACT);
}

static void goToGames(void) 
{
    Menu_changeMenu(PET_MENU_GAMES);
}

static void goToFood(void) 
{
    Menu_changeMenu(PET_MENU_FEED);
}

static void goToStatus(void)
{
    DigitDisplay_init();
    Menu_changeMenu(PET_MENU_STATUS);
}

static void returnToMain(void)
{
    Menu_changeMenu(0);
}

static void moodOption(void)
{
    int mood = Pet_getMoodNum();
    DigitDisplay_setDigit(mood/10);
}

static void friendshipOption(void)
{
    int friendship = Pet_getFriendshipNum();
    DigitDisplay_setDigit(friendship/10);
}

static void hungerOption(void)
{
    int hunger = Pet_getHungerNum();
    DigitDisplay_setDigit(hunger/10);
}


static void returnToMainDigit(void)
{
    DigitDisplay_cleanup();
    Menu_changeMenu(0);
}

// Menu Names and Functions
static char *mainNames[] = {"Interact", "Games", "Feed", "Status", "Quit"};
static void (*mainFuncs[MAX_MENU_FUNC_COUNT])(void) = {&goToInteract, &goToGames, &goToFood, &goToStatus, &Shutdown_trigger};

static char *interactNames[] = {"Pet", "Slap", "Back"};
static void (*interactFuncs[MAX_MENU_FUNC_COUNT])(void) = {&PetInteract_pet, &PetInteract_slap, &returnToMain};

static char *gamesNames[] = {"A", "B", "C", "Quit"};
static void (*gamesFuncs[MAX_MENU_FUNC_COUNT])(void) = {&printOption, &printOption, &printOption, &returnToMain};

static char *feedNames[] = {"Meal", "Snack", "Back"};
static void (*feedFuncs[MAX_MENU_FUNC_COUNT])(void) = {&PetInteract_feedMeal, &PetInteract_feedSnack, &returnToMain};

static char *statusNames[] = {"Mood", "Friendship", "Hunger", "Back"};
static void (*statusFuncs[MAX_MENU_FUNC_COUNT])(void) = {&moodOption, &friendshipOption, &hungerOption, &returnToMainDigit};

void PetMenu_init()
{
    MenuOptions_insert(mainNames, mainFuncs, 5);
    MenuOptions_insert(interactNames, interactFuncs, 3);
    MenuOptions_insert(gamesNames, gamesFuncs, 4);
    MenuOptions_insert(feedNames, feedFuncs, 3);
    MenuOptions_insert(statusNames, statusFuncs, 4);

    Menu_init();
    MenuReader_init();
}


void PetMenu_cleanup()
{
    MenuReader_cleanup();
    Menu_cleanup();
}
