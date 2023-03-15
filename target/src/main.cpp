#include <iostream>
#include "udpServer.h"
#include "utils.h"

int main() {
    std::cout << "Hello BeagleBone!\n";
    UdpServer_initialize();
    sleepForMs(5000);
    UdpServer_cleanup();
    return 0;
}