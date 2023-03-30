#include <stdio.h>

#include "menu.h"
#include "menuReader.h"
#include "pet.h"
#include "petInteract.h"
#include "shutdown.h"
#include "digitDisplay.h"

// Test functions for menu 
static void print1(void)
{
    Menu_clickedPrint();
}
static void print2(void)
{
    Menu_clickedPrint();
}

// Test function for deeper menu
static void goToFood(void) 
{
    Menu_changeMenu(1);
}

static void returnToMain(void)
{
    Menu_changeMenu(0);
}

static void moodOption(void)
{
    DigitDisplay_setDigit(1);
}

static void friendshipOption(void)
{
    DigitDisplay_setDigit(2);
}

static void hungerOption(void)
{
    DigitDisplay_setDigit(3);
}

static void statusMenu(void)
{
    DigitDisplay_init();
    Menu_changeMenu(2);
}

static void returnToMainDigit(void)
{
    DigitDisplay_cleanup();
    Menu_changeMenu(0);
}


// Menu Names and Functions
static char *mainNames[] = {"Interact", "Games", "Feed", "Status", "Quit"};
static void (*mainFuncs[MAX_MENU_FUNC_COUNT])(void) = {&print1, &print2, &goToFood, &statusMenu, &Shutdown_trigger};

static char *foodNames[] = {"Meal", "Snack", "Back"};
static void (*foodFuncs[MAX_MENU_FUNC_COUNT])(void) = {&PetInteract_feedMeal, &PetInteract_feedSnack, &returnToMain};

static char *statusNames[] = {"Mood", "Friendship", "Hunger", "Back"};
static void (*statusFuncs[MAX_MENU_FUNC_COUNT])(void) = {&moodOption, &friendshipOption, &hungerOption, &returnToMainDigit};

void PetMenu_init()
{
    MenuOptions_insert(mainNames, mainFuncs, 5);
    MenuOptions_insert(foodNames, foodFuncs, 3);
    MenuOptions_insert(statusNames, statusFuncs, 4);

    Menu_init();
    MenuReader_init();
}


void PetMenu_cleanup()
{
    MenuReader_cleanup();
    Menu_cleanup();
}
