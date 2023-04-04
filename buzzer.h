// buzzer.h
// Module to manage the Buzzer
#ifndef BUZZER_H_
#define BUZZER_H_

// Initialize/cleanup the module's data structures.
void Buzzer_init(void);
void Buzzer_cleanup(void);

void Buzzer_play(int period, int dutyCycle, int timeInMs);

#endif