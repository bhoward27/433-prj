OUT_DIR = $(HOME)/cmpt433/public/myApps

CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)g++

STD = -std=c++17
WFLAGS = -Wall -Werror
OPT = -g

all: a.out

a.out: main.cpp
	$(CC_C) $(WFLAGS) $(OPT) main.cpp -o $(OUT_DIR)/a.out

clean:
	rm -f $(OUT_DIR)/a.out
	rm -f *.o *.s *.out