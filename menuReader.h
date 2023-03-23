// menuReader.h
// Module to read the joystick and set to menu
#ifndef MENU__READER_H_
#define MENU_READER_H_

// Begin/end background thread which reads joystick inputs to menu
void MenuReader_init(void);
void MenuReader_cleanup(void);

#endif