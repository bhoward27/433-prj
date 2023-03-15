/**
 * Provides miscellaneous functions.
 */
#ifndef UTILS_H_
#define UTILS_H_

#include "int_typedefs.h"

#define MEDIUM_STRING_LEN 1024

/// Sleep the calling thread for delayInMs milliseconds.
void sleepForMs(int64 delayInMs);
int runCommand(const char* command);

#endif