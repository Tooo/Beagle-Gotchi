// menu.h
// Module to handle the menu structures
#ifndef _MENU_H_
#define _MENU_H_

// inspired by https://blog.mozilla.org/nnethercote/2012/03/07/n-ary-trees-in-c/
typedef struct {
    void (**func)(void); // Pointer to list of functions in menu set
    char ** menuNames; // Name of the menu options in the set
    int numOptions;
    int currentHighlighted; 
} MenuOptions;

typedef struct{
    MenuOptions *options; 
    int numKids; 
    struct MenuOptionNode ** kids;
} MenuOptionNode;


// Selects the current highlighted menu item
void selectMenuOption();

// Take the Menu set and print it to the screen
void printMenuOptions();

// Change the currentHighlighted in a direction 
// 0: up, 1, down, left: 2, right: 3
void moveHighlighted(int direction);

// Creates all menu options structures, call this before any other functions
void Menu_init();

#endif