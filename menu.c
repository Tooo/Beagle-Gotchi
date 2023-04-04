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

void MenuOptions_insert(char** menuNames, void (**functions)(void), int numOptions)
{
    if (menuCount > MAX_MENU_COUNT ) {
        return;
    }

    menuOptions[menuCount].func = functions;
    menuOptions[menuCount].menuNames = menuNames;
    menuOptions[menuCount].numOptions = numOptions;
    menuOptions[menuCount].currentHighlighted = 0;
    menuCount++;
}

void Menu_init(void)
{
    curMenu = &menuOptions[0];
    Menu_printOptions();
}

void Menu_cleanup(void)
{
    for (int i = 0; i < MAX_MENU_COUNT; i++) {
        menuOptions[i].func = NULL;
        menuOptions[i].menuNames = NULL;
        menuOptions[i].numOptions = 0;
        menuOptions[i].currentHighlighted = 0;
    }
    menuCount = 0;
    printf("\n");
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


void Menu_selectOption(void) 
{
    curMenu->func[curMenu->currentHighlighted]();
}

void Menu_printOptions(void)
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

void Menu_moveHighlighted(int direction)
{
    switch (direction) {
        case 0: /// Up
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

void Menu_changeMenu(int menuNum)
{
    if (menuNum > menuCount ) {
        return;
    }
    curMenu = &menuOptions[menuNum];
}

void Menu_clickedPrint(void)
{
    curMenu->menuNames[curMenu->currentHighlighted] = "Clicked";
}

int Menu_getCurrentHiglighted(void)
{
    return curMenu->currentHighlighted;
}

const char* Menu_getMenuName(int i)
{
    return curMenu->menuNames[i];
}

int Menu_getMenuSize(void) {
    return curMenu->numOptions;
}