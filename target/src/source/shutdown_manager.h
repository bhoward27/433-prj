/**
 * Provides the ShutdownManager class to control the shutdown of any threads that choose to refer to this class.
 * Threads should be written in such a way so that they run only while !isShutdownRequested().
 * isShutdownRequested() will return true after requestShutdown() has been called somewhere in the program.
 */
#ifndef SHUTDOWN_MANAGER_H_
#define SHUTDOWN_MANAGER_H_

#include <atomic>

class ShutdownManager {
    private:
        std::atomic<bool> requestedShutdown;

    public:
        ShutdownManager();
        bool isShutdownRequested();
        void requestShutdown();
};

#endif