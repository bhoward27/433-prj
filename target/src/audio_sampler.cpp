#include "audio_sampler.h"

#include <iostream>
#include <exception>
#include <string>
#include "utils.h"

#include "audioMixer.h"

int16_t sound[AUDIO_BUFFER_SIZE];


AudioSampler::AudioSampler(ShutdownManager* shutdownManager, int sampleRateHz, int windowSize, bool printUpdates)
{
    if (sampleRateHz <= 0) {
        throw std::invalid_argument(
            "sampleRateHz = " + std::to_string(sampleRateHz) + ", but sample rate must be greater than 0."
        );
    }
    if (windowSize <= 0) {
        throw std::invalid_argument(
            "windowSize = " + std::to_string(sampleRateHz) + ", but window size must be greater than 0."
        );
    }
    if (shutdownManager == nullptr) {
        std::invalid_argument("shutdownManager = nullptr");
    }

    this->shutdownManager = shutdownManager;
    this->sampleRateHz = sampleRateHz;
    this->windowSize = windowSize;
    this->printUpdates = printUpdates;
    this->samplesRead = 0;

    this->isFirstBuffer = true;
    this->isFull = false;

    AudioMixer_init();

    samplePeriodMs = 1000.0 / sampleRateHz;
    sum = 0;
    thread = std::thread([this] {run();});
}

void AudioSampler::waitForShutdown()
{
    thread.join();
    AudioMixer_cleanup();
}


static int getSound(size_t offset, size_t length, float *out_ptr) {
    return numpy::int16_to_float(sound + offset, out_ptr, length);
}

void AudioSampler::audioClassifier() {
    lock.lock();
    signal.total_length = EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
    signal.get_data = &getSound;

    res = run_classifier(&signal, &result, false);
    printf("classifier returned: %d", result.classification[0].value);
}

void AudioSampler::run()
{
    /*
    * Adapted from:
    * https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links/files/2022-student-howtos/MAX9814-SetupForPlayableAudio.pdf
    */
    int16_t buffer[AUDIO_READ_BUFFER_SIZE];
    int fd = open("/dev/iio:device0", O_RDONLY | O_NONBLOCK);
    if(fd == -1) {
        printf("ERROR: did you remember to run the mic start script?");
        exit(1);
    }
    int count = 0;
    // Discard old samples and add new ones to the window.
    while (!shutdownManager->isShutdownRequested()) {
        
        read(fd, buffer, AUDIO_READ_BUFFER_SIZE * sizeof(uint16_t));

        lock.lock();
        for(int i = 0; i < AUDIO_READ_BUFFER_SIZE; i++) {
            if(count >= AUDIO_BUFFER_SIZE) {
                count = 0;
                audioClassifier();
                // AudioMixer_pushAudio(sound, AUDIO_BUFFER_SIZE);
                // memset(sound, 0, AUDIO_BUFFER_SIZE * sizeof(int16_t));
            }
            // // int16_t temp = buffer[i];
            // // if(temp < 0) temp = 0;
            
            // sound[count] = buffer[i];

            // printf("%d\n", sound[count]);
            // count++;
            // buffer[i] *= 2;
            sound[count] = buffer[i];
        }
        // AudioMixer_pushAudio(buffer, AUDIO_READ_BUFFER_SIZE);
        // memset(sound, 0, AUDIO_BUFFER_SIZE * sizeof(int16_t));
        lock.unlock();
        sleepForDoubleMs(AUDIO_BUFFER_SLEEP);
        
        //     if(isFirstBuffer) {
        //         audioWindow.push_back(newSample);
        //     } else {
        //         audioWindow2.push_back(newSample);
        //     }
        //     if(++samplesRead == windowSize) {
        //         samplesRead = 0;
        //         if(isFirstBuffer) {
        //             int16 *arr = &audioWindow[0];
        //             AudioMixer_pushAudio(arr, windowSize);
        //             audioWindow2.clear();
        //         } else {
        //             int16 *arr = &audioWindow2[0];
        //             AudioMixer_pushAudio(arr, windowSize);
        //             audioWindow.clear();
        //         }
        //         isFirstBuffer = !isFirstBuffer;
        //         isFull = true;
        //     }
        
        // lock.unlock();

        // sleepForMs(samplePeriodMs);
    }
}

void AudioSampler::_printUpdate(double sample) {
    std::cout << sample << "\n";
}
