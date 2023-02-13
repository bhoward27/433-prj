#include <iostream>

#include "adc.h"
#include "utils.h"

int main() {
    std::cout << "Hello BeagleBone!\n";

    Adc ain1(1);
    while (true) {
        int16 input = ain1.read();
        std::cout << input << std::endl;
        std::cout << "(" << ain1.convertToVolts(input) << " volts)\n";
        sleepForMs(1000);
    }

    return 0;
}