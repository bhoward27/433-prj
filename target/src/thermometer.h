#ifndef THERMOMETER_H_
#define THERMOMETER_H_

#include "int_typedefs.h"
#include "adc.h"

// Note: ideally, don't construct more than one of this object at time.
// As there's only one thermometer IRL, should be only one thermometer in code.
class Thermometer {
    private:
        Adc ain;

    public:
        static const uint8 analogInputNum = 1;

        Thermometer();
        double read();
};

#endif