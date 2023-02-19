// menu.h
// Module to handle the menu 
#ifndef _MENU_H_
#define _MENU_H_

// inspired by https://blog.mozilla.org/nnethercote/2012/03/07/n-ary-trees-in-c/
typedef struct {
    void ** func; // Pointer to list of functions in menu set
    char ** menuNames; // Name of the menu options in the set
    int numOptions;
    int currentHighlighted; 
} MenuOptions;

typedef struct{
    MenuOptions *options; 
    int numKids; 
    struct MenuOptionNode ** kids;
} MenuOptionNode;


// Select the given option in the menu
void select_menu_option(MenuOptions options, int selection);

// Take the Menu set and print it to the screen
void print_menu_options(MenuOptionNode menuNode);


#endif