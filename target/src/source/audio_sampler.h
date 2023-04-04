/*
* audio_sampler.h
* This module starts sampling the microphone and runs the samples through
* ML fire alarm inference
* 
*/

#ifndef AUDIO_SAMPLER_H
#define AUDIO_SAMPLER_H

#include <thread>
#include <mutex>
#include <queue>

#include "shutdown_manager.h"

#define AUDIO_READ_BUFFER_SIZE 100
#define AUDIO_BUFFER_SLEEP 12

class AudioSampler {
    private:
        std::thread thread;
        std::mutex lock;
        ShutdownManager* shutdownManager = nullptr;

        //start sampling microphone and running fire alarm inference
        void run();

        void audioClassifier();
        void writeToFile(std::string filename, std::string content);

    public:
        /**
         * Start a thread that samples the microphone. The thread also
         * runs the samples through a fire alarm ML inference model.
         *
         * @param shutdownManager a pointer to the program's ShutdownManager, which will control when the AudioSampler's
         * thread stops.
         */
        AudioSampler(ShutdownManager* shutdownManager);

        /// Block until shutdownManager->requestShutdown() is called somewhere in the program.
        void waitForShutdown();

};


#endif // !AUDIO_SAMPLER_H
