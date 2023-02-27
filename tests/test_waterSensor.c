// test_waterSensor.c
// This file tests writing colours & animations using ledMatrix.h

#include "../waterSensor.h"

#include <stdio.h>

#include "../utils.h"

int main() {
    for (int i = 0; i < 3 * 40; i++) {
        bool isSubmerged = waterSensor_isSubmerged();
        double voltage = waterSensor_readVoltage();

        printf("submerged? %s @ %.4fV\n", isSubmerged ? "true" : "false", voltage);

        sleepForMs(200);
    }
}
