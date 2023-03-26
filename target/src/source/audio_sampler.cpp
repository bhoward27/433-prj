#include "audio_sampler.h"

#include <iostream>
#include <exception>
#include <string>
#include "utils.h"

#include "audioMixer.h"
#include "edge-impulse-sdk/classifier/ei_run_classifier.h"

#define AUDIO_BUFFER_SIZE EI_CLASSIFIER_SLICE_SIZE

int16_t sound[AUDIO_BUFFER_SIZE];



AudioSampler::AudioSampler(ShutdownManager* shutdownManager)
{
    if (shutdownManager == nullptr) {
        std::invalid_argument("shutdownManager = nullptr");
    }

    this->shutdownManager = shutdownManager;

    // AudioMixer_init();

    thread = std::thread([this] {run();});
}

void AudioSampler::waitForShutdown()
{
    thread.join();
    // AudioMixer_cleanup();
    run_classifier_deinit();
}


static int getSound(size_t offset, size_t length, float *out_ptr) {
    return numpy::int16_to_float(sound + offset, out_ptr, length);
}

void AudioSampler::audioClassifier() {
    signal_t signal; //wrapper for raw data
    static ei_impulse_result_t result; //classifier return
    lock.lock();
    signal.total_length = EI_CLASSIFIER_SLICE_SIZE;
    signal.get_data = &getSound;

    EI_IMPULSE_ERROR res = run_classifier_continuous(&signal, &result, false, false);
    // printf("error code: %d\n", res);
    printf("%s: %f\n", result.classification[0].label, result.classification[1].value);
    // memset(sound, 0, AUDIO_BUFFER_SIZE);
    lock.unlock();
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
    run_classifier_init();
    while (!shutdownManager->isShutdownRequested()) {
        
        read(fd, buffer, AUDIO_READ_BUFFER_SIZE * sizeof(uint16_t));

        lock.lock();
        for(int i = 0; i < AUDIO_READ_BUFFER_SIZE; i++) {
            if(count >= AUDIO_BUFFER_SIZE) {
                count = 0;
                lock.unlock();
                audioClassifier();
                lock.lock();
            }
            sound[count++] = buffer[i];
        }
        lock.unlock();
        sleepForDoubleMs(AUDIO_BUFFER_SLEEP);
    }
}
