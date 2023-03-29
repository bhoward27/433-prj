#include <iostream>

#include "heat_sampler.h"
#include "audio_sampler.h"
#include "udpServer.h"

int main() {
    std::cout << "Hello BeagleBone!\n";

    ShutdownManager shutdownManager;

    // Sample the temperature at 1 Hz and calculate window average over the last 10 samples.
    // HeatSampler heatSampler(&shutdownManager, 1, 10, true);
    // Construct like this instead if you want the sampler to not print anything:
    // HeatSampler heatSampler(&shutdownManager, 1, 10);



    // heatSampler.waitForShutdown();
    AudioSampler audioSampler(&shutdownManager);
    UdpServer_initialize();
    
    UdpServer_cleanup();
    audioSampler.waitForShutdown();

    return 0;
}