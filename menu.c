#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/ioctl.h>
#include "menu.h"

// #define tc_move_cursor(X,Y) printf("\033[%d;%df", Y, X)

void print_menu_options(MenuOptionNode menuNode, int highlighted)
{
    // Clear screen
    // Move cursor to the middle of the screen
    // Print each menu option
    for (int i=0; i<menuNode.options->numOptions; i++) {
        printf("%s\n", menuNode.options->menuNames[i]);
    }
}

// static void tc_get_cols_rows(int *cols, int *rows)
// {
//     struct winsize size; 
//     ioctl(1, TIOCGWINSZ, &size);
//     *cols = size.ws_col;
//     *rows = size.ws_row;
// }