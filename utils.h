// utils.h
// this module provides common helper functions
#ifndef UTILS_H
#define UTILS_H

// from windef.h maybe?
#ifndef NOMINMAX
    #ifndef max
    #define max(a,b)            (((a) > (b)) ? (a) : (b))
    #endif

    #ifndef min
    #define min(a,b)            (((a) < (b)) ? (a) : (b))
    #endif
#endif  /* NOMINMAX */

#include <stdio.h>
#include <stdbool.h>

// ------------------------------- //
// provided utils:

long long getTimeInMs(void);
void sleepForMs(long long delayInMs);
void runCommandExtra(const char* command, bool suppressError);
void runCommand(const char* command);

// ------------------------------- //
// custom utils:

int readIntFromFile(const char* path);
void writeIntToFilePointer(FILE* fp, int val);
void writeIntToFile(const char* path, int val);
void silentTryWriteIntToFile(const char* path, int val);
bool startswith(const char* prefix, const char* str);

bool exportGpio(int pinNum);
void setGpioDirection(int pinNum, const char* direction);

#endif