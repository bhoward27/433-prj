// Header for the webcam class
#ifndef WEBCAM_H_
#define WEBCAM_H_
#include "shutdown_manager.h"
#include <thread>

class Webcam {
    private:
        std::thread thread;
        // Run the webcam
        void run ();
        ShutdownManager *shutdownManager = nullptr;

    public:
        // Constructor
        Webcam (ShutdownManager *manager);
        // Wait for shutdown, joins the thread
        void waitForShutdown ();
};

#endif