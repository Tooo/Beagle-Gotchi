// waterSensor.h
// a tiny interface for using the water sensor.
// Make sure the water sensor is properly connected as defined in waterSensor.md before using this module.

#ifndef WATER_SENSOR_H
#define WATER_SENSOR_H

#include <stdbool.h>

bool waterSensor_isSubmerged();
double waterSensor_readVoltage();

#endif // !WATER_SENSOR_H