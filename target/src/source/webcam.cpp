#include "webcam.h"

#include "capture.h"
#include "shutdown_manager.h"
#include <iostream>
#include <thread>

Webcam::Webcam(ShutdownManager *manager)
{
    this->shutdownManager = manager;
    starterThread = std::thread([this] { run(); });
}

void Webcam::run()
{
    webcamThread = std::thread([this] { webcam(); });
    while (!shutdownManager->isShutdownRequested());
    printf("Shutdown requested, stopping webcam.\n");
    stopLoop();
}

void Webcam::waitForShutdown() {
    webcamThread.join();
    starterThread.join();
}