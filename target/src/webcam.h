#ifndef WEBCAM_H_
#define WEBCAM_H_
#include "shutdown_manager.h"
#include <thread>

class Webcam {
    private:
        std::thread thread;
        void run ();
        ShutdownManager *shutdownManager = nullptr;

    public:
        Webcam (ShutdownManager *manager);
        void checkInput ();
        void waitForShutdown ();
};

#endif