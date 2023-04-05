#include "audio_sampler.h"

#include <iostream>
#include <exception>
#include <string>
#include "utils.h"
#include <alsa/asoundlib.h>
#include "lock.h"
#include <fstream>
#include <sstream>
#include <iomanip>

#include "edge-impulse-sdk/classifier/ei_run_classifier.h"

#define AUDIO_BUFFER_SIZE EI_CLASSIFIER_SLICE_SIZE

int16_t sound[AUDIO_BUFFER_SIZE];
const std::string BUFFER_PATH = "/sys/bus/iio/devices/iio:device0/buffer/enable";


AudioSampler::AudioSampler(ShutdownManager* shutdownManager, Notifier* notifier)
{
    if (shutdownManager == nullptr) {
        std::invalid_argument("shutdownManager = nullptr");
    }
    adc_lock.lock();
    this->shutdownManager = shutdownManager;
    this->notifier = notifier;
    this->alarmValue = 0.0;

    thread = std::thread([this] {run();});
}

void AudioSampler::waitForShutdown()
{
    thread.join();
    run_classifier_deinit();
}


static int getSound(size_t offset, size_t length, float *out_ptr) {
    return numpy::int16_to_float(sound + offset, out_ptr, length);
}

void AudioSampler::audioClassifier() {
    signal_t signal; //wrapper for raw data
    static ei_impulse_result_t result; //classifier return
    signal.total_length = EI_CLASSIFIER_SLICE_SIZE;
    signal.get_data = &getSound;

    EI_IMPULSE_ERROR res = run_classifier_continuous(&signal, &result, false, false);
    // printf("error code: %d\n", res);
    updateAverage(result.classification[0].value);
    printf("%s: %f\n", result.classification[0].label, result.classification[0].value);
    printf("\n%f", alarmValue);

    if (alarmValue >= requiredCertainty) {
        std::stringstream stream;
        stream << "Fire alarm detected with "
               << std::fixed << std::setprecision(3) << alarmValue * 100 << "% certainty!";
        notifier->raiseEvent(Event::fireAlarmDetected, stream.str());
    }
    else if (alarmValue <= requiredCertainty - 0.10) {
        std::stringstream stream;
        stream << "The chance that a fire alarm is going off has lowered to only "
               << std::fixed << std::setprecision(3) << alarmValue * 100 << "%.";
        notifier->clearEvent(Event::fireAlarmDetected, stream.str());
    }
}

void AudioSampler::updateAverage(float newSample) {
    alarmValue = (alarmValue * ALARM_AVERAGE_PREVIOUS) + (newSample * ALARM_AVERAGE_NEW);
}

void AudioSampler::writeToFile(std::string filename, std::string content) {
    std::ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        std::cout << "Could not open file " << filename << std::endl;
        return;
    }
    file << content;
    file.close();
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

        for(int i = 0; i < AUDIO_READ_BUFFER_SIZE; i++) {
            if(count >= AUDIO_BUFFER_SIZE) {
                count = 0;
                writeToFile(BUFFER_PATH, "0");
                adc_lock.unlock();
                audioClassifier();
                adc_lock.lock();
                writeToFile(BUFFER_PATH, "1");
            }
            sound[count++] = buffer[i] * 2;
        }
        sleepForDoubleMs(AUDIO_BUFFER_SLEEP);
    }
}

float AudioSampler::getAlarmValue()
{
    return alarmValue;
}
