/**
 * Provides miscellaneous functions.
 */
#ifndef UTILS_H_
#define UTILS_H_

#include "int_typedefs.h"

/// Sleep the calling thread for delayInMs milliseconds.
void sleepForMs(int64 delayInMs);

// Sleep the calling thread, must be less than 1 second
void sleepForDoubleMs(double delayInMs);

#endif