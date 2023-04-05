#include "webcam.h"

#include "capture.h"
#include "shutdown_manager.h"
#include <iostream>
#include <thread>

Webcam::Webcam(ShutdownManager *manager)
{
    this->shutdownManager = manager;
    thread = std::thread([this] { run(); });
}

void Webcam::run()
{
    webcam(shutdownManager);
    if (shutdownManager->isShutdownRequested()) {
        printf("Shutdown requested, stopping webcam.\n");
        stopLoop();
    }
}

void Webcam::waitForShutdown() { thread.join(); }