#include <iostream>
#include <string>

#include "heat_sampler.h"
#include "sms.h"
#include "utils.h"
#include "notifier.h"

int main() {
    std::cout << "Hello BeagleBone!\n";

    ShutdownManager shutdownManager;
    Notifier notifier(&shutdownManager, true);

    // Sample the temperature at 1 Hz and calculate window average over the last 10 samples.
    // HeatSampler heatSampler(&shutdownManager, &notifier, 1, 10, true);
    // Construct like this instead if you want the sampler to not print anything:
    // HeatSampler heatSampler(&shutdownManager, 1, 10);

    // Sms sms(&shutdownManager, true);
    // Construct like this instead if you want Sms to not print anything:
    // Sms sms(&shutdownManager);

    // Example of queueing three messages to be sent by sms.
    notifier.raiseEvent(Event::extremeHeat, "Temperature is real darn high right now.");
    sleepForMs(500);
    // notifier.raiseEvent(Event::extremeHeat, "hot hot hot!");
    // sleepForMs(500);
    notifier.clearEvent(Event::extremeHeat);
    sleepForMs(500);
    // notifier.clearEvent(Event::extremeHeat);
    // sleepForMs(500);
    notifier.clearEvent(Event::flood);
    sleepForMs(500);
    // notifier.raiseEvent(Event::extremeHeat, "hot hot hot!");
    // sleepForMs(500);

    shutdownManager.requestShutdown();
    notifier.wakeUpSmsForShutdown();

    return 0;
}