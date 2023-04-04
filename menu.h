// menu.h
// Module to handle the menu structures
#ifndef _MENU_H_
#define _MENU_H_

#define MAX_OPTIONS_PER_ROW 1
#define MAX_MENU_FUNC_COUNT 6
#define MAX_MENU_COUNT 6

// inspired by https://blog.mozilla.org/nnethercote/2012/03/07/n-ary-trees-in-c/
typedef struct {
    void (**func)(void); // Pointer to list of functions in menu set
    char **menuNames; // Name of the menu options in the set
    int numOptions;
    int currentHighlighted; 
} MenuOptions;

// Insert menu options before initing
void MenuOptions_insert(char** menuNames, void (**functions)(void), int numOptions);

// Creates all menu options structures, call this before any other functions
void Menu_init(void);

// Free Menu Items
void Menu_cleanup(void);

// Selects the current highlighted menu item
void Menu_selectOption(void);

// Take the Menu set and print it to the screen
void Menu_printOptions(void);

// Change the currentHighlighted in a direction 
// 0: up, 1, down, left: 2, right: 3
void Menu_moveHighlighted(int direction);
void Menu_moveCursorToTop(void);

// Reverts back to the main menu
void Menu_changeMenu(int menuNum);

void Menu_clickedPrint(void);

int Menu_getCurrentHiglighted(void);

// displays the menu using the led matrix
void Menu_renderMenu(void);

#endif