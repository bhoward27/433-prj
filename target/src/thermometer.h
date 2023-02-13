#ifndef THERMOMETER_H_
#define THERMOMETER_H_

#include "int_typedefs.h"
#include "adc.h"

class Thermometer {
    private:
        Adc ain;

    public:
        static const uint8 analogInputNum = 1;

        Thermometer();
        double read();
};

#endif