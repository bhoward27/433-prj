#include <string>

#include "adc.h"

Adc::Adc(uint8 analogInputNum)
{
    if (analogInputNum > 7) {
        throw std::invalid_argument("Invalid analogInputNum -- must be in range [0, 7].");
    }
    std::string filePath =
        "/sys/bus/iio/devices/iio:device0/in_voltage" +
        std::to_string(analogInputNum) +
        "_raw";
    analogInputFile.open(filePath);
}

int16 Adc::read()
{
    int16 val = -1;
    analogInputFile >> val;
    // TODO: Check if val is in valid range [0, 4095] and log error if not.

    // Clear EOF flag.
    analogInputFile.clear();
    // Set file position back to start of the file.
    analogInputFile.seekg(0, analogInputFile.beg);
    return val;
}

double Adc::convertToVolts(double x)
{
    if (x > maxInputVal || x < minInputVal) {
        throw std::invalid_argument(
            "x = " + std::to_string(x) + ", but x must be in range [" + std::to_string(minInputVal) + ", " + std::to_string(maxInputVal) + "]"
        );
    }

    return (x / maxInputVal) * maxInputVoltage;
}

Adc::~Adc()
{
    analogInputFile.close();
}