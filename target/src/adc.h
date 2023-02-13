#ifndef ADC_H_
#define ADC_H_

#include <fstream>

#include "int_typedefs.h"

class Adc {
    private:
        uint8 analogInputNum;
        std::ifstream analogInputFile;

    public:
        static const uint8 maxAnalogInputNum = 7;
        static const int16 maxInputVal = 4095;
        static const int16 minInputVal = 0;
        static constexpr double maxInputVoltage = 1.8;

        Adc(uint8 analogInputNum);
        ~Adc();
        int16 read();
        static double convertToVolts(double x);
};

#endif