/**
 * Provides the Thermometer class to read the current temperature in degrees Celsius.
 * The current implementation requires the temperature sensor to be connected to ADC AIN1.
 */
#ifndef THERMOMETER_H_
#define THERMOMETER_H_

#include "int_typedefs.h"
#include "adc.h"

class Thermometer {
    private:
        Adc ain;

    public:
        static const uint8 analogInputNum = 2;

        Thermometer();

        /// Return the current temperature in degrees Celsius.
        double read();
};

#endif