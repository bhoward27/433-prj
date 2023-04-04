// This module provides the function to read the current voltage being output by the water level sensor.

#ifndef WATER_LEVEL_SENSOR_H
#define WATER_LEVEL_SENSOR_H

#include "notifier.h"

// Function will return the voltage reading of the pot
float WaterLevelSensor_getVoltage1Reading(Notifier* notifier);

#endif