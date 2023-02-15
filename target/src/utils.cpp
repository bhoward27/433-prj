#include <ctime>

#include "utils.h"

void sleepForMs(int64 delayInMs)
{
    const int64 NS_PER_MS = 1000 * 1000;
    const int64 NS_PER_SECOND = 1000000000;
    int64 delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}