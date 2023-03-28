#include "shutdown_manager.h"

ShutdownManager::ShutdownManager()
{
    requestedShutdown = false;
}

bool ShutdownManager::isShutdownRequested()
{
    return requestedShutdown;
}

void ShutdownManager::requestShutdown()
{
    requestedShutdown = true;
}