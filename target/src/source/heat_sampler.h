/**
 * Provides the HeatSampler class, which samples the current temperature at a specified sample rate, calculates the
 * mean temperature by simple window averaging, and notifies the user if the average temperature becomes extreme.
 */
#ifndef HEAT_SAMPLER_H_
#define HEAT_SAMPLER_H_

#include <thread>
#include <mutex>
#include <queue>
#include <string>

#include "thermometer.h"
#include "shutdown_manager.h"
#include "notifier.h"

class HeatSampler {
    public:
        // These are in degrees Celsius.
        static constexpr double extremeCold = 0.0;
        static constexpr double extremeHeat = 30.0;
        static constexpr double hysteresis = 1.0;

        const std::string degreesCSymbol = "\u2103";

        /**
         * Start a thread that samples the current temperature with a frequency of sampleRateHz. The thread also
         * does simple window averaging for the last windowSize samples. The thread notifies the user if the
         * window-averaged temperature becomes extreme.
         *
         * @param shutdownManager a pointer to the program's ShutdownManager, which will control when the HeatSampler's
         * thread stops.
         * @param notifier a pointer to the Notifier, to notify the user of extreme cold or heat conditions.
         * @param printUpdates set to true if you want an update printed to the console after each sample is taken.
         */
        HeatSampler(ShutdownManager* shutdownManager,
                    Notifier* notifier,
                    int sampleRateHz,
                    int windowSize,
                    bool printUpdates = false);

        /// Block until shutdownManager->requestShutdown() is called somewhere in the program.
        ~HeatSampler();

        /// Return the window-averaged temperature in degrees Celsius.
        double getMeanTemperature();

        /// Return all samples currently in the window.
        std::queue<double> getSamples();

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
        Notifier* notifier = nullptr;
        bool printUpdates;

        /// Main loop of HeatSampler's thread.
        void run();

        /**
         * Check if temperature is extreme, and notify the user if it is. Temperature is extreme if it is <= extremeCold
         * or >= extremeHeat. If the temperature shifts back into a reasonable temperature, the user will also be
         * notified of this, and hysteresis is used to prevent oscillation between states.
         */
        void checkForExtremeTemp(double temperature);

        // Not thread-safe.
        double _getMeanTemperature();

        // Not thread-safe.
        void _printUpdate(double newSample, double avgTemp);
};

#endif