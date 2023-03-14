// Playback sounds in real time, allowing multiple simultaneous wave files
// to be mixed together and played without jitter.

#ifndef AUDIO_MIXER_H
#define AUDIO_MIXER_H

#include <alsa/asoundlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <limits.h>
#include <alloca.h> // needed for mixer
#include "utils.h"

typedef struct {
	int numSamples;
	short *pData;
} wavedata_t;

#define AUDIOMIXER_MAX_VOLUME 100
#define AUDIOMIXER_MIN_TEMPO 40
#define AUDIOMIXER_MAX_TEMPO 300

#define BASE_DRUM "beatbox-wav-files/100051__menegass__gui-drum-bd-hard.wav"
#define HI_HAT_DRUM "beatbox-wav-files/100053__menegass__gui-drum-cc.wav"
#define SNARE_DRUM "beatbox-wav-files/100059__menegass__gui-drum-snare-soft.wav"
#if defined (__cplusplus)
extern "C" {
#endif
// init() must be called before any other functions,
// cleanup() must be called last to stop playback threads and free memory.
void AudioMixer_init(void);
void AudioMixer_cleanup(void);

// Read the contents of a wave file into the pSound structure. Note that
// the pData pointer in this structure will be dynamically allocated in
// readWaveFileIntoMemory(), and is freed by calling freeWaveFileData().
void AudioMixer_readWaveFileIntoMemory(char *fileName, wavedata_t *pSound);
void AudioMixer_freeWaveFileData(wavedata_t *pSound);

// Queue up another sound bite to play as soon as possible.
void AudioMixer_queueSound(wavedata_t *pSound);

// Get/set the volume.
// setVolume() function posted by StackOverflow user "trenki" at:
// http://stackoverflow.com/questions/6787318/set-alsa-master-volume-from-c-code
int  AudioMixer_getVolume(void);
void AudioMixer_setVolume(int newVolume);

void AudioMixer_pushAudio(int16_t *pData, int size);

//Get/set the tempo
int AudioMixer_getTempo(void);
void AudioMixer_setTempo(int newTempo);

#endif

#if defined (__cplusplus)
}
#endif
