/**
 * Provides the HeatSampler class, which samples the current temperature at a specified sample rate, and calculates the
 * mean temperature by simple window averaging.
 */
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
        /**
         * Start a thread that samples the current temperature with a frequency of sampleRateHz. The thread also
         * does simple window averaging for the last windowSize samples.
         *
         * @param shutdownManager a pointer to the program's ShutdownManager, which will control when the HeatSampler's
         * thread stops.
         * @param printUpdates set to true if you want an update printed to the console after each sample is taken.
         */
        HeatSampler(ShutdownManager* shutdownManager, int sampleRateHz, int windowSize, bool printUpdates = false);

        /// Block until shutdownManager->requestShutdown() is called somewhere in the program.
        void waitForShutdown();

        /// Return the window-averaged temperature in degrees Celsius.
        double getMeanTemperature();

        /// Return all samples currently in the window.
        std::queue<double> getSamples();
};

#endif