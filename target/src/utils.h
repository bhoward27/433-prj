/**
 * Provides miscellaneous functions.
 */
#ifndef UTILS_H_
#define UTILS_H_

#include <string>

#include "int_typedefs.h"

/// Sleep the calling thread for delayInMs milliseconds.
void sleepForMs(int64 delayInMs);

/// Return s converted to all capital letters.
std::string toUpper(std::string s);

#endif