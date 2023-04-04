/**
 * Provides a class for reading from the ADC (Analog to Digital Converter).
 */
#ifndef ADC_H_
#define ADC_H_

#include <fstream>

#include "int_typedefs.h"

class Adc {
    private:
        uint8 analogInputNum;
        std::ifstream analogInputFile;
        std::string filePath;

    public:
        static const uint8 maxAnalogInputNum = 7;
        static const int16 maxInputVal = 4095;
        static const int16 minInputVal = 0;
        static constexpr double maxInputVoltage = 1.8;

        /**
         * Open connection to ADC on analogInputNum.
         * E.g., if analogInputNum = 1, open connection to AIN1.
         */
        Adc(uint8 analogInputNum);

        /// Close connection to ADC.
        ~Adc();

        /**
         * Read from the ADC input specified by analogInputNum.
         * This returns an int16 in range [minInputVal, maxInputVal].
         */
        int16 read();

        /// Convert an ADC reading into a voltage between [0, maxInputVoltage] volts.
        static double convertToVolts(double analogInputVal);
};

#endif