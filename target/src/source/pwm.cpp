#include "pwm.h"
#include "string"
#include <fstream>

// path for left/right servo
const std::string PWM0_PATH = "/sys/class/pwm/pwmchip3/pwm0/";

PWM::PWM(ShutdownManager *shutdownManager) {
    this->shutdownManager = shutdownManager;
    this->thread = std::thread(&PWM::run, this);
}

void PWM::waitForShutdown() {
    this->thread.join();
}

void PWM::writeToFile(std::string filename, std::string content) {
    std::ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        std::cout << "Could not open file " << filename << std::endl;
        return;
    }
    file << content;
    file.close();
}

void PWM::setPeriod(int period) {
    writeToFile(PWM0_PATH + "period", std::to_string(period));
}

void PWM::setDutyCycle(int dutyCycle) {
    writeToFile(PWM0_PATH + "duty_cycle", std::to_string(dutyCycle));
    this->currentDutyCycle = dutyCycle;
}

void PWM::enablePWM() {
    writeToFile(PWM0_PATH + "enable", "1");
}

void PWM::disablePWM() {
    writeToFile(PWM0_PATH + "enable", "0");
}

void PWM::moveLeft() {
    if (!(this->currentDutyCycle - DUTY_CYCLE_CHANGE_DIRECTION < DUTY_MIN)) {
        setDutyCycle(this->currentDutyCycle - DUTY_CYCLE_CHANGE_DIRECTION);
    }
    sleepForMs(500);
}

void PWM::moveRight() {
    if (!(this->currentDutyCycle + DUTY_CYCLE_CHANGE_DIRECTION > DUTY_MAX)) {
        setDutyCycle(this->currentDutyCycle + DUTY_CYCLE_CHANGE_DIRECTION);
    }
    sleepForMs(500);
}

void PWM::run() {
    setPeriod(PERIOD_NS);
    enablePWM();
    if (shutdownManager->isShutdownRequested()) {
        disablePWM();
    }
}