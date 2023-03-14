#include "thermometer.h"

Thermometer::Thermometer() : ain(analogInputNum) {}

double Thermometer::read()
{

    double voltage = ain.convertToVolts(ain.read());

    // CITATION: Formula copied from SFU student guide:
    // https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links/files/2022-student-howtos/TMP36TemperatureSensor.pdf
    // TODO: Create a more accurate conversion formula, if possible. Readings are currently too high.
    // For example, it tells me in my room that it's 22 to 23 degrees, but my guess is that the real
    // temperature is closer to 18 degrees.
    double tempCelsius = (voltage * 1000 - 500) / 10;
    return tempCelsius;
}