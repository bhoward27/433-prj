/**
 * Provides the HeatSampler class, which samples the current temperature at a specified sample rate, and calculates the
 * mean temperature by simple window averaging.
 */
#ifndef HEAT_SAMPLER_H_
#define HEAT_SAMPLER_H_

#include <thread>
#include <mutex>
#include <queue>
#include <string>
#include <sstream>
#include <iomanip>

#include "thermometer.h"
#include "shutdown_manager.h"
#include "notifier.h"

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
        Notifier* notifier = nullptr;
        bool printUpdates;

        void run();

        // Not thread-safe.
        double _getMeanTemperature();

        // Not thread-safe.
        void _printUpdate(double newSample, double avgTemp);

        void checkExtremes(double temp)
        {
            if (temp <= extremeCold) {
                std::stringstream message;
                message << "Temperature is " << std::fixed << std::setprecision(1) << temp << degreesCSymbol
                        << ", which is colder than " << extremeCold << degreesCSymbol << "!";
                notifier->raiseEvent(Event::extremeCold, message.str());
            } else if (temp >= extremeCold + hysteresis) {
                std::stringstream message;
                message << "Warmed up to " << std::fixed << std::setprecision(1) << temp << degreesCSymbol << ".";
                notifier->clearEvent(Event::extremeCold, message.str());
            }

            if (temp >= extremeHeat) {
                std::stringstream message;
                message << "Temperature is " << std::fixed << std::setprecision(1) << temp << degreesCSymbol
                        << ", which is hotter than " << extremeHeat << degreesCSymbol << "!";
                notifier->raiseEvent(Event::extremeHeat, message.str());
            } else if (temp <= extremeHeat - hysteresis) {
                std::stringstream message;
                message << "Cooled down to " << std::fixed << std::setprecision(1) << temp << degreesCSymbol << ".";
                notifier->clearEvent(Event::extremeHeat, message.str());
            }
        }

    public:
        static constexpr double extremeCold = 0.0;
        static constexpr double extremeHeat = 30.0;
        static constexpr double hysteresis = 1.0;

        const std::string degreesCSymbol = "\u2103";

        /**
         * Start a thread that samples the current temperature with a frequency of sampleRateHz. The thread also
         * does simple window averaging for the last windowSize samples.
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
};

#endif