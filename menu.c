#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "menu.h"

#define MAX_OPTIONS_PER_ROW 2
#define MAX_NUM_MENU_FUNCTIONS 4

// The current menu printed
MenuOptionNode * curMenuNode;

// Main menu node
MenuOptionNode mainMenu;
MenuOptions mainMenuOptions;
// Sub menu
MenuOptionNode subMenuNode;
MenuOptions subMenuOptions;

// Our functions and menu names
char * mainMenuNames[] = {"Interact", "Games", "Status", "Feed"};

char * subMenuNames[] = {"Food", "Back"};

// Test functions for menu 
static void print1(void)
{
    MenuOptions * currentMenuOptions = curMenuNode->options;
    currentMenuOptions->menuNames[currentMenuOptions->currentHighlighted] = "Clicked1";
}
static void print2(void)
{
    MenuOptions * currentMenuOptions = curMenuNode->options;
    currentMenuOptions->menuNames[currentMenuOptions->currentHighlighted] = "Clicked2";
}
static void print3(void)
{
    MenuOptions * currentMenuOptions = curMenuNode->options;
    currentMenuOptions->menuNames[currentMenuOptions->currentHighlighted] = "Clicked3";
}
static void print4(void) // Test function for deeper menu
{
    curMenuNode = &subMenuNode;
}

static void print5(void)
{
    MenuOptions * currentMenuOptions = curMenuNode->options;
    currentMenuOptions->menuNames[currentMenuOptions->currentHighlighted] = "Clicked5";
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


void selectMenuOption() 
{
    MenuOptions * currentMenuOptions = curMenuNode->options;

    currentMenuOptions->func[currentMenuOptions->currentHighlighted]();
}

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

void setBackToMainMenu()
{
    curMenuNode = &mainMenu;
}

void Menu_init()
{
    // Init the main menu
    mainMenuOptions.func = malloc(sizeof(void(*)(void)) * MAX_NUM_MENU_FUNCTIONS);
    mainMenuOptions.func[0] = &print1;
    mainMenuOptions.func[1] = &print2;
    mainMenuOptions.func[2] = &print3;
    mainMenuOptions.func[3] = &print4;

    mainMenuOptions.menuNames = mainMenuNames;
    mainMenuOptions.numOptions = 4;
    mainMenuOptions.currentHighlighted = 0;

    mainMenu.options = &mainMenuOptions;
    mainMenu.numKids = 0;

    // Set the current menu as the mainMenu
    curMenuNode = &mainMenu;

    // Create Submenu
    subMenuOptions.func = malloc(sizeof(void(*)(void)) * MAX_NUM_MENU_FUNCTIONS);
    subMenuOptions.func[0] = &print5;
    subMenuOptions.func[1] = &setBackToMainMenu;

    subMenuOptions.menuNames = subMenuNames;
    subMenuOptions.numOptions = 2;
    subMenuOptions.currentHighlighted = 0;

    subMenuNode.options = &subMenuOptions;
    subMenuNode.numKids = 0;

    // Set the current menu as the mainMenu
    curMenuNode = &mainMenu;

    printMenuOptions();
}

void Menu_cleanup()
{
    void (**menuPtr)(void) = mainMenuOptions.func;
    free(menuPtr);
    menuPtr = subMenuOptions.func;
    free(menuPtr);
}
