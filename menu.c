#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "menu.h"

#define tc_move_cursor(X,Y) printf("\033[%d;%df", Y, X)
#define MAX_OPTIONS_PER_ROW 2

// Test functions for menu 
static void print1(void)
{
    printf("test1\n");
}
static void print2(void)
{
    printf("test2\n");
}
static void print3(void)
{
    printf("test3\n");
}
static void print4(void) 
{
    printf("test4\n");
}

MenuOptionNode * curMenuNode;

// Create main menu node
MenuOptionNode mainMenu;

MenuOptions mainMenuOptions;

// Our functions and menu names
void * mainMenuFunctions[] = {&print1, &print2, &print3, &print4};
char * mainMenuNames[] = {"print1", "p2", "print3", "print4"};

// Gets the terminal window size in columns and rows
static void tc_get_cols_rows(int *cols, int *rows);

void printMenuOptions()
{
    // Clear screen
    printf("\033c");

    // Move cursor to the middle of the screen
    int xScreen = 0;
    int yScreen = 0;
    tc_get_cols_rows(&xScreen, &yScreen);
    tc_move_cursor(xScreen/2, yScreen/2);

    MenuOptions * currentMenuOptions = curMenuNode->options;

    // Print each menu option
    for (int i=0; i<currentMenuOptions->numOptions; i++) {
        if (i > 0 && i % MAX_OPTIONS_PER_ROW == 0) {
            // Go to the next line
            tc_move_cursor(xScreen/2, (yScreen/2) + (i/MAX_OPTIONS_PER_ROW));
        }
        if (i == currentMenuOptions->currentHighlighted) {
            printf("[ %-10s ]", currentMenuOptions->menuNames[i]);
        }
        else {
            printf("  %-10s  ", currentMenuOptions->menuNames[i]);
        }
    }
    fflush(stdout);
}

void moveHighlighted (int direction)
{
    MenuOptions * currentMenuOptions = curMenuNode->options;
    switch (direction) {
        case 0:/// Up
            if (currentMenuOptions->currentHighlighted - MAX_OPTIONS_PER_ROW >= 0) {
                currentMenuOptions->currentHighlighted = currentMenuOptions->currentHighlighted - MAX_OPTIONS_PER_ROW;
            }
            break;
        case 1: // Down
            if (currentMenuOptions->currentHighlighted + MAX_OPTIONS_PER_ROW < currentMenuOptions->numOptions) {
                currentMenuOptions->currentHighlighted = currentMenuOptions->currentHighlighted + MAX_OPTIONS_PER_ROW;
            }
            break;
        case 2: // Left
            if (currentMenuOptions->currentHighlighted % MAX_OPTIONS_PER_ROW != 0) {
                currentMenuOptions->currentHighlighted = currentMenuOptions->currentHighlighted - 1;
            }
            break;
        case 3:
            if ((currentMenuOptions->currentHighlighted + 1) % MAX_OPTIONS_PER_ROW != 0) {
                currentMenuOptions->currentHighlighted = currentMenuOptions->currentHighlighted + 1;
            }
            break;
    }
}

void Menu_init()
{
    // Init the main menu
    mainMenuOptions.func = mainMenuFunctions;
    mainMenuOptions.menuNames = mainMenuNames;
    mainMenuOptions.numOptions = 4;
    mainMenuOptions.currentHighlighted = 0;

    mainMenu.options = &mainMenuOptions;
    mainMenu.numKids = 0;

    // Set the current menu as the mainMenu
    curMenuNode = &mainMenu;

    printMenuOptions();
    // Create menu thread to keep printing
}

static void tc_get_cols_rows(int *cols, int *rows)
{
    struct winsize size; 
    ioctl(1, TIOCGWINSZ, &size);
    *cols = size.ws_col;
    *rows = size.ws_row;
}