#ifndef HEAT_SAMPLER_H_
#define HEAT_SAMPLER_H_

#include <thread>
#include <mutex>
#include <queue>

#include "thermometer.h"
#include "shutdown_manager.h"

class HeatSampler {
    private:
        Thermometer thermometer;
        int sampleRateHz;
        int windowSize;
        double samplePeriodMs;
        double sum;
        std::queue<double> samples;
        std::thread thread;
        std::mutex lock;
        ShutdownManager* shutdownManager = nullptr;
        bool printUpdates;

        void run();

        // Not thread-safe.
        double _getMeanTemperature();

        // Not thread-safe.
        void _printUpdate(double newSample);

    public:
        HeatSampler(ShutdownManager* shutdownManager, int sampleRateHz, int windowSize, bool printUpdates = false);
        void waitForShutdown();
        double getMeanTemperature();
};

#endif