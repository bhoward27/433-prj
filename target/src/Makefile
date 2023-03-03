OUT_DIR = $(HOME)/cmpt433/public/myApps

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)g++

STD = -std=c++17
WFLAGS = -Wall -Werror
OPT = -g
CPP_FILES = main.cpp adc.cpp utils.cpp thermometer.cpp shutdown_manager.cpp heat_sampler.cpp capture.c webcam.cpp

all: a.out

a.out: $(CPP_FILES)
	$(CC_C) $(WFLAGS) $(OPT) $(CPP_FILES) -pthread -o $(OUT_DIR)/a.out

clean:
	rm -f $(OUT_DIR)/a.out
	rm -f *.o *.s *.out