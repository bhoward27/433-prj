#ifndef PWM_H_
#define PWM_H_
#include "shutdown_manager.h"
#include "utils.h"
#include <iostream>
#include <thread>

#define PERIOD_NS 20000000

#define DUTY_CYCLE_0 1000000
#define DUTY_CYCLE_90 1500000
#define DUTY_CYCLE_180 2000000

#define DUTY_CYCLE_CHANGE_DIRECTION 500000

class PWM {
    private:
        std::thread thread;
        int currentDutyCycle = 0;
        void run();
        void writeToFile(std::string filename, std::string content);
        void setPeriod(int period);
        void setDutyCycle(int dutyCycle);
        void enablePWM();
        void disablePWM();
        void moveLeft();
        void moveRight();
        ShutdownManager *shutdownManager = nullptr;

    public:
        // Constructor
        PWM(ShutdownManager *shutdownManager);
        // Wait for shutdown, joins the thread
        void waitForShutdown();
};

#endif
