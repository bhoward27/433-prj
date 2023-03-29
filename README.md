# Home Defense System

## Directory Structure
There are two main folders: target and host.
target contains all files relevant to code which runs on the target (the BeagleBone Green).
host contains all files relevant to code which runs on the host (Debian PC/VM).
### Source Code
    Source code on host goes into the src folder within the host folder.
    Souce code on target goes in the src/source folder within the target folder


## Dependencies
You will need the g++ cross-compiler to build the code in target/src. To install it, run this command on your host:
`sudo apt install g++-arm-linux-gnueabihf`

## Hardware Setup
To get temperature readings, the TMP36 temperature sensor must be wired up to the BeagleBone as shown in this student guide (NOTE: this guide was not created by The Defenders): https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links/files/2022-student-howtos/TMP36TemperatureSensor.pdf
For our project, the sensor must be connected to AIN1.

To get microphone readings, the MAX9814 microphone must be wired with VDD to 3.3v power, GND to ground, and OUT to AIN4(pin 33)
Before using the microphone after each reboot, the user must run startMic.sh

### Libraries
    We are using the Edge Impulse library
        - ML library targetted towards embedded systems
        - Website allows training of an ML model
        - Edge Impulse library allows on-device inference of trained model
        - https://www.edgeimpulse.com/
