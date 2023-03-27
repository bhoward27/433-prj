#include <iostream>
#include <string>

#include "heat_sampler.h"
#include "notifier.h"
#include "shutdown_manager.h"

int main() {
    std::cout << "Hello BeagleBone!\n";

    ShutdownManager shutdownManager;
    Notifier notifier(&shutdownManager, true);

    // Sample the temperature at 1 Hz and calculate window average over the last 10 samples.
    HeatSampler heatSampler(&shutdownManager, &notifier, 1, 10, true);

    return 0;
}