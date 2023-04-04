#include <ctime>
#include <bits/stdc++.h>

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

void sleepForDoubleMs(double delayInMs)
{
    const int64 NS_PER_MS = 1000 * 1000;
    double delayNs = delayInMs * (double)NS_PER_MS;
    int seconds = 0;
    int nanoseconds = delayNs;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}

std::string toUpper(std::string s)
{
    // CITATION: Code copied from here:
    // https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/.
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);

    return s;
}

std::string toLower(std::string s)
{
    // CITATION: Code copied from here:
    // https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/.
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);

    return s;
}
