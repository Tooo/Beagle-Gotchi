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

#define MAX_BUFFER_SIZE 256

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
void writeBufferToFile(const char* path, const char* buffer);

bool startswith(const char* prefix, const char* str);

bool exportGpio(int pinNum);
void setGpioDirection(int pinNum, const char* direction);
void setGpioValue(int pinNum, const char* value);

int initI2cBus(char* bus, int address);
void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);
unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr);
void readMultipleI2cReg(int i2cFileDesc, unsigned char startAddr, unsigned char* buffer, int size);

#endif