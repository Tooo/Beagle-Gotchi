#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/ioctl.h>
#include "menu.h"

#define tc_move_cursor(X,Y) printf("\033[%d;%df", Y, X)
#define MAX_OPTIONS_PER_ROW 2

static void tc_get_cols_rows(int *cols, int *rows);

void print_menu_options(MenuOptionNode menuNode)
{
    MenuOptions * menuOptions = menuNode.options;
    // Clear screen
    printf("\033c");

    // Move cursor to the middle of the screen
    int xScreen = 0;
    int yScreen = 0;
    tc_get_cols_rows(&xScreen, &yScreen);
    tc_move_cursor(xScreen/2, yScreen/2);

    // Print each menu option
    for (int i=0; i<menuOptions->numOptions; i++) {
        if (i > 0 && i % MAX_OPTIONS_PER_ROW == 0) {
            // Go to the next line
            tc_move_cursor(xScreen/2, (yScreen/2) + (i/MAX_OPTIONS_PER_ROW));
        }
        if (i == menuOptions->currentHighlighted) {
            printf("[ %-10s ]", menuOptions->menuNames[i]);
        }
        else {
            printf("  %-10s  ", menuOptions->menuNames[i]);
        }
    }
}

static void tc_get_cols_rows(int *cols, int *rows)
{
    struct winsize size; 
    ioctl(1, TIOCGWINSZ, &size);
    *cols = size.ws_col;
    *rows = size.ws_row;
}