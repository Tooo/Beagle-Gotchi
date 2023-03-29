#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "menu.h"

// The current menu printed
static MenuOptions* curMenu;

// Our functions and menu names
static MenuOptions menuOptions[MAX_MENU_COUNT];
static int menuCount = 0;

// Test functions for menu 
static void print1(void)
{
    curMenu->menuNames[curMenu->currentHighlighted] = "Clicked1";
}
static void print2(void)
{
    curMenu->menuNames[curMenu->currentHighlighted] = "Clicked2";
}
static void print3(void)
{
    curMenu->menuNames[curMenu->currentHighlighted] = "Clicked3";
}
static void print4(void) // Test function for deeper menu
{
    curMenu = &menuOptions[1];
}

static void print5(void)
{
    curMenu->menuNames[curMenu->currentHighlighted] = "Clicked5";
}

static void print6(void)
{
    curMenu->menuNames[curMenu->currentHighlighted] = "Clicked5";
}

static char *mainMenuNames[] = {"Interact", "Games", "Status", "Feed", "Quit"};
static void (*mainFuncs[MAX_MENU_FUNC_COUNT])(void) = {&print1, &print2, &print3, &print4, &print5};

static char *subMenuNames[] = {"Meal", "Back"};
static void (*subFuncs[MAX_MENU_FUNC_COUNT])(void) = {&print6, &Menu_setBackToMainMenu};

// void MenuOptions_insert(char** menuNames, void (**functions)(void), int numOptions)
// {
//     if (menuCount < MAX_MENU_COUNT ) {
//         return;
//     }

//     menuOptions[menuCount].func = functions;
//     menuOptions[menuCount].menuNames = menuNames;
//     menuOptions[menuCount].numOptions = numOptions;
//     menuOptions[menuCount].currentHighlighted = 0;
//     menuCount++;
// }

void Menu_init()
{
    // Init the main menu
    //MenuOptions_insert(mainMenuNames, mainFuncs, 5);
    menuOptions[menuCount].func = mainFuncs;
    menuOptions[menuCount].menuNames = mainMenuNames;
    menuOptions[menuCount].numOptions = 5;
    menuOptions[menuCount].currentHighlighted = 0;

    menuCount++;

    // Set the current menu as the mainMenu
    curMenu = &menuOptions[0];

    // Create Submenu
    //MenuOptions_insert(subMenuNames, subFuncs, 2);
    menuOptions[menuCount].func = subFuncs;
    menuOptions[menuCount].menuNames = subMenuNames;
    menuOptions[menuCount].numOptions = 2;
    menuOptions[menuCount].currentHighlighted = 0;

    Menu_printOptions();
}

void Menu_cleanup()
{
    // nothing
}

// Gets the terminal window size in columns and rows
static void tc_get_cols_rows(int *cols, int *rows)
{
    struct winsize size; 
    ioctl(1, TIOCGWINSZ, &size);
    *cols = size.ws_col;
    *rows = size.ws_row;
}

// Moves the cursor to x and y in the terminal
static void tc_move_cursor(int x, int y)
{
    printf("\033[%d;%df", y, x);
}


void Menu_selectOption() 
{
    curMenu->func[curMenu->currentHighlighted]();
}

void Menu_printOptions()
{
    // Clear screen
    printf("\033c");

    // Move cursor to the middle of the screen
    int xScreen = 0;
    int yScreen = 0;
    tc_get_cols_rows(&xScreen, &yScreen);
    tc_move_cursor(xScreen/2, yScreen/2);

    // Print each menu option
    for (int i=0; i<curMenu->numOptions; i++) {
        if (i > 0 && i % MAX_OPTIONS_PER_ROW == 0) {
            // Go to the next line
            tc_move_cursor(xScreen/2, (yScreen/2) + (i/MAX_OPTIONS_PER_ROW));
        }
        if (i == curMenu->currentHighlighted) {
            printf("[ %-10s ]", curMenu->menuNames[i]);
        }
        else {
            printf("  %-10s  ", curMenu->menuNames[i]);
        }
    }
    fflush(stdout);
}

void Menu_moveHighlighted (int direction)
{
    switch (direction) {
        case 0:/// Up
            if (curMenu->currentHighlighted - MAX_OPTIONS_PER_ROW >= 0) {
                curMenu->currentHighlighted -= MAX_OPTIONS_PER_ROW;
            }
            break;
        case 1: // Down
            if (curMenu->currentHighlighted + MAX_OPTIONS_PER_ROW < curMenu->numOptions) {
                curMenu->currentHighlighted += MAX_OPTIONS_PER_ROW;
            }
            break;
        case 2: // Left
            if (curMenu->currentHighlighted % MAX_OPTIONS_PER_ROW != 0) {
                curMenu->currentHighlighted -= 1;
            }
            break;
        case 3:
            if ((curMenu->currentHighlighted + 1) % MAX_OPTIONS_PER_ROW != 0 
                && (curMenu->currentHighlighted + 1) < curMenu->numOptions) {
                curMenu->currentHighlighted += 1;
            }
            break;
    }
}

void Menu_setBackToMainMenu()
{
    curMenu = &menuOptions[0];
}