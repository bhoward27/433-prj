// Code provided by Dr. Fraser
// Demo application to read analog input voltage 1 on the BeagleBone
// Assumes ADC cape already loaded by uBoot:

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include "utils.h"

#define A2D_FILE_VOLTAGE1  "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
#define A2D_VOLTAGE_REF_V  1.8
#define A2D_MAX_READING    4095



float WaterLevelSensor_getVoltage1Reading()
{
	// Open file
	FILE *f = fopen(A2D_FILE_VOLTAGE1, "r");
	if (!f) {
		printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
		printf("       Check /boot/uEnv.txt for correct options.\n");
		exit(-1);
	}

	// Get reading
	int a2dReading = 0;
	int itemsRead = fscanf(f, "%d", &a2dReading);
	if (itemsRead <= 0) {
		printf("ERROR: Unable to read values from voltage input file.\n");
		exit(-1);
	}

	// Close file
	fclose(f);
	if (a2dReading == 0) {
		a2dReading++;
	}
	return (a2dReading*(A2D_VOLTAGE_REF_V/A2D_MAX_READING))*2;
}



