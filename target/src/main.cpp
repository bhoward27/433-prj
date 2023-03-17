#include <iostream>
#include <string>

#include "heat_sampler.h"
#include "sms.h"
#include "utils.h"

int main() {
    std::cout << "Hello BeagleBone!\n";

    ShutdownManager shutdownManager;

    // TODO: Add back in after wired up.
    // // Sample the temperature at 1 Hz and calculate window average over the last 10 samples.
    // HeatSampler heatSampler(&shutdownManager, 1, 10, true);
    // // Construct like this instead if you want the sampler to not print anything:
    // // HeatSampler heatSampler(&shutdownManager, 1, 10);

    Sms sms(&shutdownManager);

    for (int i = 0; i < 3; i++) {
        sms.queueMessage(std::to_string(i));
        std::cout << "Queued message " << i << ".\n";
        sleepForMs(500);
    }

    shutdownManager.requestShutdown();
    sms.wakeUpForShutdown();

    return 0;
}