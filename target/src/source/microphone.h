/**
 * Provides the Thermometer class to read the current temperature in degrees Celsius.
 * The current implementation requires the temperature sensor to be connected to ADC AIN1.
 */
#ifndef MICROPHONE_H_
#define MICROPHONE_H_

#include "int_typedefs.h"
#include "adc.h"

class Microphone {
    private:
        Adc ain;

    public:
        static const uint8 analogInputNum = 4;

        Microphone();

        /// Return the current temperature in degrees Celsius.
        int16 read();
};

#endif