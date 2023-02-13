#include <iostream>

#include "utils.h"
#include "thermometer.h"

int main() {
    std::cout << "Hello BeagleBone!\n";

    Thermometer t;
    while (true) {
        std::cout << t.read() << " degrees Celsius" << std::endl;
        sleepForMs(1000);
    }

    return 0;
}