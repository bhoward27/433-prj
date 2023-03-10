OUT_DIR = $(HOME)/cmpt433/public/myApps

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)g++

STD = -std=c++17
WFLAGS = -Wall -Werror
OPT = -g
CPP_FILES = main.cpp adc.cpp utils.cpp thermometer.cpp shutdown_manager.cpp heat_sampler.cpp microphone.cpp audio_sampler.cpp audioMixer.c

LFLAGS = -L$(HOME)/cmpt433/public/asound_lib_BBB

all: a.out

a.out: $(CPP_FILES)
	$(CC_C) $(WFLAGS) $(OPT) $(CPP_FILES) -lasound -pthread -o $(OUT_DIR)/a.out $(LFLAGS)
micScript:
	cp startMic.sh $(OUT_DIR)/startMic.sh
	cp stopMic.sh $(OUT_DIR)/stopMic.sh

clean:
	rm -f $(OUT_DIR)/a.out
	rm -f *.o *.s *.out