OUT_DIR = $(HOME)/cmpt433/public/myApps

SSLDIR = /usr/arm-linux-gnueabihf/openssl
ZDIR = /usr/arm-linux-gnueabihf/zlib
CURLDIR = /usr/arm-linux-gnueabihf/curl

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)g++

STD = -std=c++17
WFLAGS = -Wall -Werror
OPT = -g
CFLAGS = $(STD) $(OPT) $(WFLAGS)

INCLUDE = -I$(CURLDIR)/include -I$(SSLDIR)/include -I$(ZDIR)/include
LDFLAGS = -L$(CURLDIR)/lib -Wl,-rpath -Wl,$(CURLDIR)/lib -L$(SSLDIR)/lib -Wl,-rpath -Wl,$(SSLDIR)/lib -L$(ZDIR)/lib -Wl,-rpath -Wl,$(ZDIR)/lib
LDLIBS = -lcurl -pthread

CPP_FILES = main.cpp adc.cpp utils.cpp thermometer.cpp shutdown_manager.cpp heat_sampler.cpp twilio/twilio.cpp

all: a.out

a.out: $(CPP_FILES)
	$(CC_C) -o $(OUT_DIR)/a.out $(INCLUDE) $(LDFLAGS) $(CFLAGS) $(CPP_FILES) $(LDLIBS)
clean:
	rm -f $(OUT_DIR)/a.out
	rm -f *.o *.s *.out