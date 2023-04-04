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

// duty cycle is 0.5ms to 2.5ms
#define DUTY_MIN 500000
#define DUTY_MAX 2500000

// change the duty cycle by 0.25ms
#define DUTY_CYCLE_CHANGE_DIRECTION 250000

// Move the servo left or right, returns true if worked, returns false if failed
bool moveLeft();
bool moveRight();

// Set the period of the PWM signal
void setPeriod(int period);
// Set the duty cycle of the PWM signal
void setDutyCycle(int dutyCycle);

// Function to write to a file
void writeToFile(std::string filename, std::string content);

class PWM
{
private:
    std::thread thread;
    void run();
    ShutdownManager *shutdownManager = nullptr;

public:
    // Constructor
    PWM(ShutdownManager *shutdownManager);
    // Wait for shutdown, joins the thread
    void waitForShutdown();
    // Enable or disable the PWM signal
    void enablePWM();
    void disablePWM();
};

#endif
