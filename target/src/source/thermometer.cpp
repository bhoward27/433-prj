#include "thermometer.h"

Thermometer::Thermometer() : ain(analogInputNum) {}

double Thermometer::read()
{

    double voltage = ain.convertToVolts(ain.read());

    // CITATION: Formula based on SFU student guide, adjusted for voltage divider setup:
    // https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links/files/2022-student-howtos/TMP36TemperatureSensor.pdf
    double tempCelsius = (voltage * 2000 - 500) / 10;
    return tempCelsius;
}