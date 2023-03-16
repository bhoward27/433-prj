#include <iostream>
#include "udpServer.h"
#include "utils.h"
#include "waterLevelSensor.h"
#include "utils.h"
int main() {
    std::cout << "Hello BeagleBone!\n";
    UdpServer_initialize();
    for(int i=0; i<10; i++) {
        printf("%f\n", WaterLevelSensor_getVoltage1Reading());
        sleepForMs(1000);
    }
    UdpServer_cleanup();
    return 0;
}