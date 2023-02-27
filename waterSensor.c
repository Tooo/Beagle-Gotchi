#include "waterSensor.h"

#include "a2d.h"

// AIN6 is p9_36
const int WATER_SENSOR_AIN_ID = 6;

bool waterSensor_isSubmerged() {
    const int WETNESS_LIMIT = 4096/4; // lower bound voltage for wetness
    return a2d_readValue(WATER_SENSOR_AIN_ID) > WETNESS_LIMIT;
}

double waterSensor_readVoltage() {
    return a2d_readVoltage(WATER_SENSOR_AIN_ID);
}