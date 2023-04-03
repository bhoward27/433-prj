# Home Defense System

## Directory Structure
There are two main folders: target and host.
target contains all files relevant to code which runs on the target (the BeagleBone Green).
host contains all files relevant to code which runs on the host (Debian PC/VM).
### Source Code
    Source code on host goes into the src folder within the host folder.
    Souce code on target goes in the src/source folder within the target folder


## Dependencies
You will need the g++ cross-compiler to build the code in target/src. To install it (and some additional libraries required by the webcam), run this command on your host:
`sudo apt install g++-arm-linux-gnueabihf ffmpeg v4l-utils libv4l-dev`
You will also need to install some additional cross-compiled libraries that are required by Twilio SMS service: OpenSSL, zlib, and curl.
These must be installed to /usr/arm-linux-gnueabihf on your host. Run the following command on your host to do so:
`./installTwilioDependencies.sh`
Note: when the above script is downloading source code, it may fail to connect several times. This is normal, just wait and eventually it should succeed.
If the file `target/src/source/twilio/config.h` is not present, ask for the file from a team member.
Regardless, please change the `toPhoneNumber` constant in that file to your own personal phone number (add +1 in front for Canadian numbers).

## Hardware Setup
To get temperature readings, the TMP36 temperature sensor must be wired up to the BeagleBone with a voltage divider setup, with the sensor's Vout connected to AIN2 on the ADC. Ask Ben if you don't know how to wire it up.

For webcam Pan and Tilt, use the P9_21 pin for the servo's PWM connection on bottom servo motor. The rest of the setup is in this student guide: https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links/files/2022-student-howtos-ensc351/ServoPanTiltGuide.pdf The student guide uses both servo motors, but we only use the bottom one, so only the setup for Servo 1 is required.

To get microphone readings, the MAX9814 microphone must be wired with VDD to 3.3v power, GND to ground, and OUT to AIN4(pin 33)
Before using the microphone after each reboot, the user must run startMic.sh

## How to Build the App on Your Host Machine
Ensure that you have NFS set up and running between the host machine and the BeagleBone. Then, on the host:
`cd target/src`
`make`

# How to Run the App on the BBG
On the BBG, navigate to myApps in the NFS folder. Then:
`./app`

### Libraries
    We are using the Edge Impulse library
        - ML library targetted towards embedded systems
        - Website allows training of an ML model
        - Edge Impulse library allows on-device inference of trained model
        - https://www.edgeimpulse.com/
