#include "a2d.h"

#include <stdio.h>
#include <stdlib.h>

#include "../utils.h"

// AIN0 is mapped to the potentiometer in the zen cape
const int VALID_AIN_IDS[] = { 0, 1, 2, 3, 4, 5, 6 };

const int MAX_12BIT = 4095;
const double MAX_VOLTAGE = 1.8;

double a2d_readVoltage(int ainID) {
    int value12bit = a2d_readValue(ainID);
    return ((double)value12bit / (double)MAX_12BIT) * MAX_VOLTAGE;
}

int a2d_readValue(int ainID) {
    const int MAX_PATH_LEN = 128;
    char pathBuf[MAX_PATH_LEN];
    sprintf(pathBuf, "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw", ainID);

    int value12bit = readIntFromFile(pathBuf);
    return value12bit;
}