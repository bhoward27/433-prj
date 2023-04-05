#include <iostream>

#include "shutdown_manager.h"
#include "notifier.h"
#include "heat_sampler.h"
#include "audio_sampler.h"
#include "webcam.h"
#include "pwm.h"
#include "udpServer.h"
#include "utils.h"

int main() {
    std::cout << "Hello BeagleBone!\n";

    ShutdownManager shutdownManager;
    Notifier notifier(&shutdownManager, true);

    AudioSampler audioSampler(&shutdownManager, &notifier);
    sleepForMs(100);
    // Sample the temperature at 1 Hz and calculate window average over the last 10 samples.
    HeatSampler heatSampler(&shutdownManager, &notifier, 1, 10, true);
    UdpServer_initialize(&shutdownManager, &heatSampler, &notifier, &audioSampler);
    Webcam webcam(&shutdownManager);
    PWM pwm(&shutdownManager);

    webcam.waitForShutdown();
    pwm.waitForShutdown();
    UdpServer_cleanup();
    audioSampler.waitForShutdown();
}
