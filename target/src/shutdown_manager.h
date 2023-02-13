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