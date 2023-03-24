#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "ledDisplay.h"
#include "utils.h"

// I2C bus and address
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2C_DEVICE_ADDRESS 0x20

// I2C values for LED Display
#define REG_DIRA 0x00
#define REG_DIRB 0x01
#define REG_OUTA 0x14
#define REG_OUTB 0x15

// GPIO values for LED Display
static int gpioDigits[2] = {61, 44};

// Top and Bottom values for LED Display Patterns
static unsigned char topPattern[10] = {0x86, 0x12, 0x0E, 0x06, 0x8A, 0x8C, 0x8C, 0x14, 0x8E, 0x8E};
static unsigned char bottomPattern[10] = {0xA1, 0x80, 0x31, 0xB0, 0x90, 0xB0, 0xB1, 0x04, 0xB1, 0x90};

// I2C file descriptor
static int i2cFileDesc;

// File setup functions
static void Display_setDigitHardware(int digit);
static void Display_setGpioValueAll(char* value);

// Display thread
static pthread_t displayThread;
static void* Display_threadFunction(void* arg);
static bool stopping;

// Displaying digit
static int displayDigit;

void Display_init(void)
{
    runCommand("config-pin P9_18 i2c");
    runCommand("config-pin P9_17 i2c");

    for (int i = 0; i < 2; i++) {
        setGpioDirection(gpioDigits[i], "out");
    }

    i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);

    writeI2cReg(i2cFileDesc, REG_DIRA, 0x00);
    writeI2cReg(i2cFileDesc, REG_DIRB, 0x00);

    stopping = false;
    pthread_create(&displayThread, NULL, &Display_threadFunction, NULL);
}

void Display_cleanup(void)
{
    stopping = true;
    pthread_join(displayThread, NULL);
    Display_setGpioValueAll("0");
    close(i2cFileDesc);
}

void Display_setDigit(int digit)
{
    displayDigit = digit;
}


static void* Display_threadFunction(void* arg)
{
    (void)arg;
    while(!stopping) {
        Display_setDigitHardware(displayDigit);
    }
    return NULL;
}

static void Display_setDigitHardware(int digit)
{
    if (digit > 99) {
        digit = 99;
    }

    if (digit < 0) {
        digit = 0;
    }

    int leftNum = digit / 10;
    int rightNum = digit - (leftNum * 10);
    int digitArray[] = {leftNum, rightNum};

    for (int i = 0; i < 2; i++)
    {
        Display_setGpioValueAll("0");
        
        int digitValue = digitArray[i];
        writeI2cReg(i2cFileDesc, REG_OUTA, bottomPattern[digitValue]);
        writeI2cReg(i2cFileDesc, REG_OUTB, topPattern[digitValue]);

        setGpioValue(gpioDigits[i], "1");

        sleepForMs(5);
    }
    Display_setGpioValueAll("0");
}


static void Display_setGpioValueAll(char* value)
{
    for (int i = 0; i < 2; i++) {
        setGpioValue(gpioDigits[i], value);
    }
}