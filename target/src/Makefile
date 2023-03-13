# OUT_DIR = $(HOME)/cmpt433/public/myApps

# CROSS_COMPILE = arm-linux-gnueabihf-
# CC_C = $(CROSS_COMPILE)g++

# STD = -std=c++17
# WFLAGS = 
# OPT = -g
# CPP_FILES = main.cpp adc.cpp utils.cpp thermometer.cpp shutdown_manager.cpp heat_sampler.cpp microphone.cpp audio_sampler.cpp audioMixer.c 
# CPP_FILES += $(wildcard edge-impulse-sdk/tensorflow/lite/kernels/*.cc) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/kernels/internal/*.cc) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/kernels/*.cc) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/*.cc) \
# 				$(wildcard edge-impulse-sdk/porting/posix/*.c*) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/memory_planner/*.cc) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/core/api/*.cc)
# CPP_FILES += edge-impulse-sdk/tensorflow/lite/c/common.c
# CPP_FILES += $(wildcard edge-impulse-sdk/tensorflow/lite/kernels/*.cc) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/kernels/internal/*.cc) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/kernels/*.cc) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/*.cc) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/memory_planner/*.cc) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/core/api/*.cc)
# # CPP_FILES += ./edge-impulse-sdk/porting/linux/ei_classifier_porting.cpp ./edge-impulse-sdk/porting/linux/debug_log.cpp
# # CPP_FILES += edge-impulse-sdk/dsp/kissfft/kiss_fft.cpp edge-impulse-sdk/dsp/kissfft/kiss_fftr.cpp
# # CPP_FILES += tflite-model/trained_model_compiled.cpp edge-impulse-sdk/tensorflow/lite/micro/kernels/conv.cc edge-impulse-sdk/tensorflow/lite/micro/kernels/conv_common.cc
# # CPP_FILES += edge-impulse-sdk/tensorflow/lite/micro/kernels/tflite_detection_postprocess.cc
# # CPP_FILES += edge-impulse-sdk/tensorflow/lite/kernels/kernel_util_lite.cc
# # CPP_FILES += edge-impulse-sdk/tensorflow/lite/micro/kernels/add.cc

# LFLAGS = -L$(HOME)/cmpt433/public/asound_lib_BBB 
# LIBRARY = -I.

# all: a.out micScript

# a.out: $(CPP_FILES)
# 	$(CC_C) $(WFLAGS) $(OPT) $(LIBRARY) $(CPP_FILES) -lasound  -pthread -o $(OUT_DIR)/a.out $(LFLAGS)
# micScript:
# 	cp startMic.sh $(OUT_DIR)/startMic.sh
# 	cp stopMic.sh $(OUT_DIR)/stopMic.sh

# clean:
# 	rm -f $(OUT_DIR)/a.out
# 	rm -f *.o *.s *.out


# Tool macros
# CC ?= arm-linux-gnueabihf-gcc
# CXX ?= arm-linux-gnueabihf-g++

# # Settings
# NAME = app
# BUILD_PATH = ./build

# # Location of main.cpp (must use C++ compiler for main)
# CXXSOURCES = main.cpp adc.cpp utils.cpp thermometer.cpp shutdown_manager.cpp heat_sampler.cpp microphone.cpp audio_sampler.cpp

# # Search path for header files (current directory)
# CFLAGS += -I.

# # C and C++ Compiler flags
# CFLAGS += -Wall						# Include all warnings
# CFLAGS += -g						# Generate GDB debugger information
# CFLAGS += -Wno-strict-aliasing		# Disable warnings about strict aliasing
# CFLAGS += -Os						# Optimize for size
# CFLAGS += -DNDEBUG					# Disable assert() macro
# CFLAGS += -DEI_CLASSIFIER_ENABLE_DETECTION_POSTPROCESS_OP	# Add TFLite_Detection_PostProcess operation

# # C++ only compiler flags
# CXXFLAGS += -std=c++14				# Use C++14 standard

# # Linker flags
# LDFLAGS += -lm 						# Link to math.h
# LDFLAGS += -lstdc++					# Link to stdc++.h
# LDFLAGS += -lasound -pthread 

# # Include C source code for required libraries
# CSOURCES += $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/*.c) \
# 			$(wildcard edge-impulse-sdk/CMSIS/DSP/Source/CommonTables/*.c) \
# 			$(wildcard edge-impulse-sdk/CMSIS/DSP/Source/BasicMathFunctions/*.c) \
# 			$(wildcard edge-impulse-sdk/CMSIS/DSP/Source/ComplexMathFunctions/*.c) \
# 			$(wildcard edge-impulse-sdk/CMSIS/DSP/Source/FastMathFunctions/*.c) \
# 			$(wildcard edge-impulse-sdk/CMSIS/DSP/Source/SupportFunctions/*.c) \
# 			$(wildcard edge-impulse-sdk/CMSIS/DSP/Source/MatrixFunctions/*.c) \
# 			$(wildcard edge-impulse-sdk/CMSIS/DSP/Source/StatisticsFunctions/*.c)
# CSOURCES += audioMixer.c 

# # Include C++ source code for required libraries
# CXXSOURCES += 	$(wildcard tflite-model/*.cpp) \
# 				$(wildcard edge-impulse-sdk/dsp/kissfft/*.cpp) \
# 				$(wildcard edge-impulse-sdk/dsp/dct/*.cpp) \
# 				$(wildcard edge-impulse-sdk/dsp/memory.cpp) \
# 				$(wildcard edge-impulse-sdk/porting/posix/*.c*) \
# 				$(wildcard edge-impulse-sdk/porting/mingw32/*.c*)
# CCSOURCES +=

# # Use TensorFlow Lite for Microcontrollers (TFLM)
# CFLAGS += -DTF_LITE_DISABLE_X86_NEON=1
# CFLAGS += -L$(HOME)/cmpt433/public/asound_lib_BBB

# CSOURCES +=	edge-impulse-sdk/tensorflow/lite/c/common.c
# CCSOURCES +=	$(wildcard edge-impulse-sdk/tensorflow/lite/kernels/*.cc) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/kernels/internal/*.cc) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/kernels/*.cc) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/*.cc) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/micro/memory_planner/*.cc) \
# 				$(wildcard edge-impulse-sdk/tensorflow/lite/core/api/*.cc)

# # Include CMSIS-NN if compiling for an Arm target that supports it
# ifeq (${CMSIS_NN}, 1)

# 	# Include CMSIS-NN and CMSIS-DSP header files
# 	CFLAGS += -Iedge-impulse-sdk/CMSIS/NN/Include/
# 	CFLAGS += -Iedge-impulse-sdk/CMSIS/DSP/PrivateInclude/

# 	# C and C++ compiler flags for CMSIS-NN and CMSIS-DSP
# 	CFLAGS += -Wno-unknown-attributes 					# Disable warnings about unknown attributes
# 	CFLAGS += -DEI_CLASSIFIER_TFLITE_ENABLE_CMSIS_NN=1	# Use CMSIS-NN functions in the SDK
# 	CFLAGS += -D__ARM_FEATURE_DSP=1 					# Enable CMSIS-DSP optimized features
# 	CFLAGS += -D__GNUC_PYTHON__=1						# Enable CMSIS-DSP intrisics (non-C features)

# 	# Include C source code for required CMSIS libraries
# 	CSOURCES += $(wildcard edge-impulse-sdk/CMSIS/NN/Source/ActivationFunctions/*.c) \
# 				$(wildcard edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/*.c) \
# 				$(wildcard edge-impulse-sdk/CMSIS/NN/Source/ConcatenationFunctions/*.c) \
# 				$(wildcard edge-impulse-sdk/CMSIS/NN/Source/ConvolutionFunctions/*.c) \
# 				$(wildcard edge-impulse-sdk/CMSIS/NN/Source/FullyConnectedFunctions/*.c) \
# 				$(wildcard edge-impulse-sdk/CMSIS/NN/Source/NNSupportFunctions/*.c) \
# 				$(wildcard edge-impulse-sdk/CMSIS/NN/Source/PoolingFunctions/*.c) \
# 				$(wildcard edge-impulse-sdk/CMSIS/NN/Source/ReshapeFunctions/*.c) \
# 				$(wildcard edge-impulse-sdk/CMSIS/NN/Source/SoftmaxFunctions/*.c) \
# 				$(wildcard edge-impulse-sdk/CMSIS/NN/Source/SVDFunctions/*.c)
# endif

# # Generate names for the output object files (*.o)
# COBJECTS := $(patsubst %.c,%.o,$(CSOURCES))
# CXXOBJECTS := $(patsubst %.cpp,%.o,$(CXXSOURCES))
# CCOBJECTS := $(patsubst %.cc,%.o,$(CCSOURCES))

# # Default rule
# .PHONY: all
# all: app

# # Compile library source code into object files
# $(COBJECTS) : %.o : %.c
# $(CXXOBJECTS) : %.o : %.cpp
# $(CCOBJECTS) : %.o : %.cc
# %.o: %.c
# 	$(CC) $(CFLAGS) -c $^ -o $@
# %.o: %.cc
# 	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $^ -o $@
# %.o: %.cpp
# 	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $^ -o $@

# # Build target (must use C++ compiler)
# .PHONY: app
# app: $(COBJECTS) $(CXXOBJECTS) $(CCOBJECTS)
# ifeq ($(OS), Windows_NT)
# 	if not exist build mkdir build
# else
# 	mkdir -p $(BUILD_PATH)
# endif
# 	$(CXX) $(COBJECTS) $(CXXOBJECTS) $(CCOBJECTS) -o $(BUILD_PATH)/$(NAME) $(LDFLAGS)

# # Remove compiled object files
# .PHONY: clean
# clean:
# ifeq ($(OS), Windows_NT)
# 	del /Q $(subst /,\,$(patsubst %.c,%.o,$(CSOURCES))) >nul 2>&1 || exit 0
# 	del /Q $(subst /,\,$(patsubst %.cpp,%.o,$(CXXSOURCES))) >nul 2>&1 || exit 0
# 	del /Q $(subst /,\,$(patsubst %.cc,%.o,$(CCSOURCES))) >nul 2>&1 || exit 0
# else
# 	rm -f $(COBJECTS)
# 	rm -f $(CCOBJECTS)
# 	rm -f $(CXXOBJECTS)
# endif

EI_SDK?=edge-impulse-sdk
PYTHON_CROSS_PATH?=

UNAME_S := $(shell uname -s)

CFLAGS +=  -Wall -g -Wno-strict-aliasing
CFLAGS += -I.
CFLAGS += -Isource
CFLAGS += -Imodel-parameters
CFLAGS += -Itflite-model
CFLAGS += -Ithird_party/
CFLAGS += -Iutils/
CFLAGS += -Os
CFLAGS += -DNDEBUG
CFLAGS += -DEI_CLASSIFIER_ENABLE_DETECTION_POSTPROCESS_OP=1
CFLAGS += -g
CFLAGS += -Wno-asm-operand-widths
CXXFLAGS += -std=c++14
LDFLAGS += -lm -lstdc++ -lasound -pthread -L$(HOME)/cmpt433/public/asound_lib_BBB 

CC ?= arm-linux-gnueabihf-gcc
CXX ?= arm-linux-gnueabihf-g++

CSOURCES = $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/*.c) $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/CommonTables/*.c) $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/BasicMathFunctions/*.c) $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/ComplexMathFunctions/*.c) $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/FastMathFunctions/*.c) $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/SupportFunctions/*.c) $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/MatrixFunctions/*.c) $(wildcard edge-impulse-sdk/CMSIS/DSP/Source/StatisticsFunctions/*.c)
CXXSOURCES = $(wildcard tflite-model/*.cpp) $(wildcard edge-impulse-sdk/dsp/kissfft/*.cpp) $(wildcard edge-impulse-sdk/dsp/dct/*.cpp) $(wildcard ./edge-impulse-sdk/dsp/memory.cpp) $(wildcard edge-impulse-sdk/porting/posix/*.c*) $(wildcard edge-impulse-sdk/porting/mingw32/*.c*)
CCSOURCES =

CXXSOURCES += main.cpp adc.cpp utils.cpp thermometer.cpp shutdown_manager.cpp heat_sampler.cpp microphone.cpp audio_sampler.cpp
CSOURCES += audioMixer.c

ifeq (${TARGET_RENESAS_RZV2L},1)
USE_FULL_TFLITE=1
TARGET_LINUX_AARCH64=1
endif

ifeq (${TARGET_TDA4VM},1)
CFLAGS += -I${TIDL_TOOLS_PATH} -I${TIDL_TOOLS_PATH}/osrt_deps
LDFLAGS +=  -L./tidl-rt/linux-aarch64 -lti_rpmsg_char -lvx_tidl_rt

ifeq (${USE_ONNX},1)
CFLAGS += -I${TIDL_TOOLS_PATH}/osrt_deps/onnxruntime/include -I${TIDL_TOOLS_PATH}/osrt_deps/onnxruntime/include/onnxruntime -I${TIDL_TOOLS_PATH}/osrt_deps/onnxruntime/include/onnxruntime/core/session
CFLAGS += -DDISABLEFLOAT16 -DXNN_ENABLE=0
LDFLAGS += -Wl,--no-as-needed -lonnxruntime -ldl -ldlr -lpthread #-lpcre -lffi -lz -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -ltbb -ljpeg -lwebp -lpng16 -ltiff -lyaml-cpp

else
USE_FULL_TFLITE=1
TARGET_LINUX_AARCH64=1
endif
endif

ifeq (${USE_FULL_TFLITE},1)
CFLAGS += -DEI_CLASSIFIER_USE_FULL_TFLITE=1
CFLAGS += -Itensorflow-lite/

ifeq (${TARGET_LINUX_ARMV7},1)
LDFLAGS += -L./tflite/linux-armv7 -Wl,--no-as-needed -ldl -ltensorflow-lite -lfarmhash -lfft2d_fftsg -lfft2d_fftsg2d -lflatbuffers -lruy -lXNNPACK -lpthreadpool -lpthread -lcpuinfo -lclog
endif # TARGET_LINUX_ARMV7
ifeq (${TARGET_LINUX_AARCH64},1)
CFLAGS += -DDISABLEFLOAT16
LDFLAGS += -L./tflite/linux-aarch64 -Wl,--no-as-needed -ldl -ltensorflow-lite -lfarmhash -lfft2d_fftsg -lfft2d_fftsg2d -lruy -lXNNPACK -lcpuinfo -lpthreadpool -lclog -lpthread
endif # TARGET_LINUX_AARCH64
ifeq (${TARGET_LINUX_X86},1)
LDFLAGS += -L./tflite/linux-x86 -Wl,--no-as-needed -ldl -ltensorflow-lite -lfarmhash -lfft2d_fftsg -lfft2d_fftsg2d -lruy -lXNNPACK -lcpuinfo -lpthreadpool -lclog -lpthread
endif # TARGET_LINUX_X86
ifeq (${TARGET_MAC_X86_64},1)
LDFLAGS += -L./tflite/mac-x86_64 -ltensorflow-lite -lcpuinfo -lfarmhash -lfft2d_fftsg -lfft2d_fftsg2d -lruy -lXNNPACK -lpthreadpool -lclog
endif # TARGET_MAC_X86_64

else ifeq (${USE_AKIDA},1) # USE_FULL_TFLITE

ifeq (${TARGET_LINUX_AARCH64},1)
CFLAGS += -DDISABLEFLOAT16
CFLAGS += -DPYBIND11_DETAILED_ERROR_MESSAGES
CFLAGS += $(shell $(PYTHON_CROSS_PATH)python3-config --cflags)
LDFLAGS += -rdynamic $(shell $(PYTHON_CROSS_PATH)python3-config --ldflags --embed)
else ifeq (${TARGET_LINUX_X86},1) # TARGET_LINUX_AARCH64
CFLAGS += $(shell python3-config --cflags)
CFLAGS += -DPYBIND11_DETAILED_ERROR_MESSAGES
LDFLAGS += -rdynamic $(shell python3-config --ldflags --embed)
endif # TARGET_LINUX_X86

else # not USE_FULL_TFLITE and not USE_AKIDA

CFLAGS += -DTF_LITE_DISABLE_X86_NEON=1
CSOURCES += edge-impulse-sdk/tensorflow/lite/c/common.c
CCSOURCES += $(wildcard edge-impulse-sdk/tensorflow/lite/kernels/*.cc) $(wildcard edge-impulse-sdk/tensorflow/lite/kernels/internal/*.cc) $(wildcard edge-impulse-sdk/tensorflow/lite/micro/kernels/*.cc) $(wildcard edge-impulse-sdk/tensorflow/lite/micro/*.cc) $(wildcard edge-impulse-sdk/tensorflow/lite/micro/memory_planner/*.cc) $(wildcard edge-impulse-sdk/tensorflow/lite/core/api/*.cc)

endif # not USE_FULL_TFLITE and not USE_AKIDA

ifeq (${TARGET_JETSON_NANO},1)
TENSORRT_VERSION=$(strip $(shell dpkg -l | grep '^ii' | grep libnvinfer[0-9] | grep -o -E '[0-9]+' | head -1 | sed -e 's/^0\+//'))
$(info TENSORRT_VERSION is ${TENSORRT_VERSION})
ifeq (${TENSORRT_VERSION},8)
LDFLAGS += tflite/linux-jetson-nano/libei_debug.a -L/usr/local/cuda-10.2/targets/aarch64-linux/lib/ -lcudart -lnvinfer -lnvonnxparser  -Wl,--warn-unresolved-symbols,--unresolved-symbols=ignore-in-shared-libs
else ifeq (${TENSORRT_VERSION},7)
LDFLAGS += tflite/linux-jetson-nano/libei_debug7.a -L/usr/local/cuda-10.2/targets/aarch64-linux/lib/ -lcudart -lnvinfer -lnvonnxparser  -Wl,--warn-unresolved-symbols,--unresolved-symbols=ignore-in-shared-libs
else
$(error Invalid TensorRT version - supported versions are 7 and 8.)
endif # TENSORRT_VERSION
endif # TARGET_JETSON_NANO

ifeq (${APP_CUSTOM},1)
NAME = custom
else ifeq (${APP_AUDIO},1)
NAME = audio
CXXSOURCES += source/audio.cpp
LDFLAGS += -lasound
else ifeq (${APP_CAMERA},1)
NAME = camera
CFLAGS += -Iopencv/build_opencv/ -Iopencv/opencv/include -Iopencv/opencv/3rdparty/include -Iopencv/opencv/3rdparty/quirc/include -Iopencv/opencv/3rdparty/carotene/include -Iopencv/opencv/3rdparty/ittnotify/include -Iopencv/opencv/3rdparty/openvx/include -Iopencv/opencv/modules/video/include -Iopencv/opencv/modules/flann/include -Iopencv/opencv/modules/core/include -Iopencv/opencv/modules/stitching/include -Iopencv/opencv/modules/imgproc/include -Iopencv/opencv/modules/objdetect/include -Iopencv/opencv/modules/gapi/include -Iopencv/opencv/modules/world/include -Iopencv/opencv/modules/ml/include -Iopencv/opencv/modules/imgcodecs/include -Iopencv/opencv/modules/dnn/include -Iopencv/opencv/modules/dnn/src/vkcom/include -Iopencv/opencv/modules/dnn/src/ocl4dnn/include -Iopencv/opencv/modules/dnn/src/tengine4dnn/include -Iopencv/opencv/modules/videoio/include -Iopencv/opencv/modules/highgui/include -Iopencv/opencv/modules/features2d/include -Iopencv/opencv/modules/ts/include -Iopencv/opencv/modules/photo/include -Iopencv/opencv/modules/calib3d/include
CXXSOURCES += source/camera.cpp
ifeq ($(UNAME_S),Linux) # on Linux set the library paths as well
LDFLAGS += -L/usr/local/lib -Wl,-R/usr/local/lib
endif
LDFLAGS += -lopencv_ml -lopencv_objdetect -lopencv_stitching  -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core
else ifeq (${APP_COLLECT},1)
NAME = collect
CXXSOURCES += source/collect.cpp
CSOURCES += $(wildcard ingestion-sdk-c/QCBOR/src/*.c) $(wildcard ingestion-sdk-c/mbedtls/library/*.c)
CFLAGS += -Iingestion-sdk-c/mbedtls/include -Iingestion-sdk-c/mbedtls/crypto/include -Iingestion-sdk-c/QCBOR/inc -Iingestion-sdk-c/QCBOR/src -Iingestion-sdk-c/inc -Iingestion-sdk-c/inc/signing
else ifeq (${APP_EIM},1)
NAME = model.eim
CXXSOURCES += source/eim.cpp
CFLAGS += -Ithird_party/
else
$(error Missing application, should have either APP_CUSTOM=1, APP_AUDIO=1, APP_CAMERA=1, APP_COLLECT=1 or APP_EIM=1)
endif

COBJECTS := $(patsubst %.c,%.o,$(CSOURCES))
CXXOBJECTS := $(patsubst %.cpp,%.o,$(CXXSOURCES))
CCOBJECTS := $(patsubst %.cc,%.o,$(CCSOURCES))

all: runner

.PHONY: runner clean

$(COBJECTS) : %.o : %.c
$(CXXOBJECTS) : %.o : %.cpp
$(CCOBJECTS) : %.o : %.cc

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.cc
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $^ -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $^ -o $@

runner: $(COBJECTS) $(CXXOBJECTS) $(CCOBJECTS)
	mkdir -p build
	$(CXX) $(COBJECTS) $(CXXOBJECTS) $(CCOBJECTS) -o build/$(NAME) $(LDFLAGS)

clean:
	rm -f $(COBJECTS)
	rm -f $(CCOBJECTS)
	rm -f $(CXXOBJECTS)