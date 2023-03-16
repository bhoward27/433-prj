#include <iostream>
#include "udpServer.h"
#include "utils.h"
#include "waterLevelSensor.h"
#include "utils.h"
int main() {
    std::cout << "Hello BeagleBone!\n";
    UdpServer_initialize();
    UdpServer_cleanup();
    return 0;
}