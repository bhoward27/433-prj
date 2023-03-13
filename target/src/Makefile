OUT_DIR = $(HOME)/cmpt433/public/myApps

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)g++

STD = -std=c++17
WFLAGS = 
OPT = -g
CPP_FILES = main.cpp adc.cpp utils.cpp thermometer.cpp shutdown_manager.cpp heat_sampler.cpp microphone.cpp audio_sampler.cpp audioMixer.c 
CPP_FILES += $(wildcard edge-impulse-sdk/tensorflow/lite/kernels/*.cc) \
				$(wildcard edge-impulse-sdk/tensorflow/lite/kernels/internal/*.cc) \
				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/kernels/*.cc) \
				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/*.cc) \
				$(wildcard edge-impulse-sdk/porting/posix/*.c*) \
				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/memory_planner/*.cc) \
				$(wildcard edge-impulse-sdk/tensorflow/lite/core/api/*.cc)
CPP_FILES += edge-impulse-sdk/tensorflow/lite/c/common.c
CPP_FILES += $(wildcard edge-impulse-sdk/tensorflow/lite/kernels/*.cc) \
				$(wildcard edge-impulse-sdk/tensorflow/lite/kernels/internal/*.cc) \
				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/kernels/*.cc) \
				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/*.cc) \
				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/memory_planner/*.cc) \
				$(wildcard edge-impulse-sdk/tensorflow/lite/core/api/*.cc)
# CPP_FILES += ./edge-impulse-sdk/porting/linux/ei_classifier_porting.cpp ./edge-impulse-sdk/porting/linux/debug_log.cpp
# CPP_FILES += edge-impulse-sdk/dsp/kissfft/kiss_fft.cpp edge-impulse-sdk/dsp/kissfft/kiss_fftr.cpp
# CPP_FILES += tflite-model/trained_model_compiled.cpp edge-impulse-sdk/tensorflow/lite/micro/kernels/conv.cc edge-impulse-sdk/tensorflow/lite/micro/kernels/conv_common.cc
# CPP_FILES += edge-impulse-sdk/tensorflow/lite/micro/kernels/tflite_detection_postprocess.cc
# CPP_FILES += edge-impulse-sdk/tensorflow/lite/kernels/kernel_util_lite.cc
# CPP_FILES += edge-impulse-sdk/tensorflow/lite/micro/kernels/add.cc

LFLAGS = -L$(HOME)/cmpt433/public/asound_lib_BBB 
LIBRARY = -I.

all: a.out micScript

a.out: $(CPP_FILES)
	$(CC_C) $(WFLAGS) $(OPT) $(LIBRARY) $(CPP_FILES) -lasound  -pthread -o $(OUT_DIR)/a.out $(LFLAGS)
micScript:
	cp startMic.sh $(OUT_DIR)/startMic.sh
	cp stopMic.sh $(OUT_DIR)/stopMic.sh

clean:
	rm -f $(OUT_DIR)/a.out
	rm -f *.o *.s *.out

