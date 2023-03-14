
#ifndef AUDIO_SAMPLER_H
#define AUDIO_SAMPLER_H

#include <thread>
#include <mutex>
#include <queue>

#include "microphone.h"
#include "shutdown_manager.h"

#define AUDIO_READ_BUFFER_SIZE 100
#define AUDIO_BUFFER_SLEEP 12

class AudioSampler {
    private:
        Microphone mic;
        int sampleRateHz;
        int windowSize;
        double samplePeriodMs;
        double sum;
        std::queue<double> samples;
        std::vector<int16> audioWindow;
        std::vector<int16> audioWindow2;
        int samplesRead;
        std::thread thread;
        std::mutex lock;
        ShutdownManager* shutdownManager = nullptr;
        bool isFull;
        bool isFirstBuffer;
        bool printUpdates;

        void run();

        // Not thread-safe.
        void _printUpdate(double newSample);

        void audioClassifier();

        // int getSound(size_t offset, size_t length, float *out_ptr);

    public:
        /**
         * Start a thread that samples the current temperature with a frequency of sampleRateHz. The thread also
         * does simple window averaging for the last windowSize samples.
         *
         * @param shutdownManager a pointer to the program's ShutdownManager, which will control when the HeatSampler's
         * thread stops.
         * @param printUpdates set to true if you want an update printed to the console after each sample is taken.
         */
        AudioSampler(ShutdownManager* shutdownManager, int sampleRateHz, int windowSize, bool printUpdates = false);

        /// Block until shutdownManager->requestShutdown() is called somewhere in the program.
        void waitForShutdown();

};


#endif // !AUDIO_SAMPLER_H