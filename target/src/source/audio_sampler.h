
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
        std::thread thread;
        std::mutex lock;
        ShutdownManager* shutdownManager = nullptr;

        //start sampling microphone and running fire alarm inference
        void run();

        void audioClassifier();

        // int getSound(size_t offset, size_t length, float *out_ptr);

    public:
        /**
         * Start a thread that samples the current temperature with a frequency of sampleRateHz. The thread also
         * does simple window averaging for the last windowSize samples.
         *
         * @param shutdownManager a pointer to the program's ShutdownManager, which will control when the AudioSampler's
         * thread stops.
         */
        AudioSampler(ShutdownManager* shutdownManager);

        /// Block until shutdownManager->requestShutdown() is called somewhere in the program.
        void waitForShutdown();

};


#endif // !AUDIO_SAMPLER_H
