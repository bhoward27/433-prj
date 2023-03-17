# Home Defense System

Directory Structure
There are two main folders: target and host.
target contains all files relevant to code which runs on the target (the BeagleBone Green).
host contains all files relevant to code which runs on the host (Debian PC/VM).
Source code goes into the src folder within the target or host folder.

Dependencies
(It is assumed that the gcc cross-compiler and binutils have already been installed (as any students would have done for assignment 1).)
You will need the g++ cross-compiler to build the code in target/src. To install it, run this command on your host:
`sudo apt install g++-arm-linux-gnueabihf`
You will also need to install some additional cross-compiled libraries that are required by Twilio SMS service: OpenSSL, zlib, and curl.
These must be installed to /usr/arm-linux-gnueabihf on your host. Run the following command on your host to do so:
`./installTwilioDependencies.sh`
Note: when the above script is downloading source code, it may fail to connect several times. This is normal, just wait and eventually it should succeed.
If the file `target/src/twilio/config.h` is not present, ask for the file from a team member.
Regardless, please change the `toPhoneNumber` constant in that file to your own personal phone number (add +1 in front for Canadian numbers).

Hardware Setup
To get temperature readings, the TMP36 temperature sensor must be wired up to the BeagleBone as shown in this student guide (NOTE: this guide was not created by The Defenders): https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links/files/2022-student-howtos/TMP36TemperatureSensor.pdf
For our project, the sensor must be connected to AIN1.
# TODO: Update the above section for wiring up with voltage divider + adjust conversion formula in code (likely just multiply by 2).