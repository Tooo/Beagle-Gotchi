// test_waterSensor.c
// Test water sensor
// Detects if water sensor is submerged or not
#include <stdio.h>

#include "../hardware/waterSensor.h"
#include "../utils/utils.h"

int main() {
    for (int i = 0; i < 3 * 40; i++) {
        bool isSubmerged = waterSensor_isSubmerged();
        double voltage = waterSensor_readVoltage();

        printf("submerged? %s @ %.4fV\n", isSubmerged ? "true" : "false", voltage);

        sleepForMs(200);
    }
}
