#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "menu.h"

// The current menu printed
static MenuOptions* curMenu;

// Main menu node
static MenuOptions mainMenu;

// Sub menu
static MenuOptions subMenu;

// Our functions and menu names
static char * mainMenuNames[] = {"Interact", "Games", "Status", "Feed"};

static char * subMenuNames[] = {"Food", "Back"};

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
    curMenu = &subMenu;
}

static void print5(void)
{
    curMenu->menuNames[curMenu->currentHighlighted] = "Clicked5";
}

void Menu_init()
{
    // Init the main menu
    mainMenu.func[0] = &print1;
    mainMenu.func[1] = &print2;
    mainMenu.func[2] = &print3;
    mainMenu.func[3] = &print4;

    mainMenu.menuNames = mainMenuNames;
    mainMenu.numOptions = 4;
    mainMenu.currentHighlighted = 0;

    // Set the current menu as the mainMenu
    curMenu = &mainMenu;

    // Create Submenu
    subMenu.func[0] = &print5;
    subMenu.func[1] = &Menu_setBackToMainMenu;

    subMenu.menuNames = subMenuNames;
    subMenu.numOptions = 2;
    subMenu.currentHighlighted = 0;

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
            if ((curMenu->currentHighlighted + 1) % MAX_OPTIONS_PER_ROW != 0) {
                curMenu->currentHighlighted += 1;
            }
            break;
    }
}

void Menu_setBackToMainMenu()
{
    curMenu = &mainMenu;
}