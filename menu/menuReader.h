// menuReader.h
// Module to read the joystick and set to menu
#ifndef MENU_READER_H_
#define MENU_READER_H_

#include <stdbool.h>

// Set the menu to print or not
void MenuReader_allowTerminalIO(bool enabled);

// Begin/end background thread which reads joystick inputs to menu
void MenuReader_init(void);
void MenuReader_cleanup(void);

#endif