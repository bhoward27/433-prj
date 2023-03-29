// Header file for the PWM class
#ifndef PWM_H_
#define PWM_H_
#include "shutdown_manager.h"
#include "utils.h"
#include <iostream>
#include <thread>

// defines for the timing of the PWM signal
// period is 20ms
#define PERIOD_NS 20000000

// duty cycle is 1ms to 2ms
#define DUTY_CYCLE_0 1000000
#define DUTY_CYCLE_90 1500000
#define DUTY_CYCLE_180 2000000

// change the duty cycle by 0.5ms
#define DUTY_CYCLE_CHANGE_DIRECTION 500000

class PWM {
    private:
        std::thread thread;
        int currentDutyCycle = 0;
        void run();
        // Function to write to a file
        void writeToFile(std::string filename, std::string content);
        // Set the period of the PWM signal
        void setPeriod(int period);
        // Set the duty cycle of the PWM signal
        void setDutyCycle(int dutyCycle);
        // Enable or disable the PWM signal
        void enablePWM();
        void disablePWM();
        // Move the servo left or right
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