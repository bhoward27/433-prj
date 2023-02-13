#include <iostream>

#include "utils.h"
// #include "thermometer.h"
#include "heat_sampler.h"

// TODO: Add comments to all added code/files before merge request.

int main() {
    std::cout << "Hello BeagleBone!\n";

    ShutdownManager shutdownManager;

    HeatSampler heatSampler(&shutdownManager, 1, 10, true);
    // Construct like this instead if you want the sampler to not print anything:
    // HeatSampler heatSampler(&shutdownManager, 1, 10);

    heatSampler.waitForShutdown();

    return 0;
}