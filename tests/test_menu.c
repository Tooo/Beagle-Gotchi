#include <stdio.h>
#include "../shutdown.h"
#include "../menu.h"
#include "../menuReader.h"

// Initialize/cleanup the module's data structures.

// Test functions for menu 
static void print1(void)
{
    Menu_clickedPrint();
}
static void print2(void)
{
    Menu_clickedPrint();
}
static void print3(void)
{
    Menu_clickedPrint();
}
static void print4(void) // Test function for deeper menu
{
    Menu_changeMenu(1);
}

static void print5(void)
{
    Menu_clickedPrint();
}

static void print6(void)
{
    Menu_clickedPrint();
}

static void print7(void)
{
    Menu_changeMenu(0);
}

static char *mainMenuNames[] = {"Interact", "Games", "Status", "Feed", "Quit"};
static void (*mainFuncs[MAX_MENU_FUNC_COUNT])(void) = {&print1, &print2, &print3, &print4, &print5};

static char *subMenuNames[] = {"Meal", "Back"};
static void (*subFuncs[MAX_MENU_FUNC_COUNT])(void) = {&print6, &print7};

int main(void)
{
    MenuOptions_insert(mainMenuNames, mainFuncs, 5);
    MenuOptions_insert(subMenuNames, subFuncs, 2);

    Menu_init();
    MenuReader_init();

    getchar();

    MenuReader_cleanup();
    Menu_cleanup();

    return 0;
}
