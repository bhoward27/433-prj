# Home Defense System

Directory Structure
There are two main folders: target and host.
target contains all files relevant to code which runs on the target (the BeagleBone Green).
host contains all files relevant to code which runs on the host (Debian PC/VM).
Source code goes into the src folder within the target or host folder.

Dependencies
You will need the g++ cross-compiler to build the code in target/src. To install it, run this command on your host:
`sudo apt install g++-arm-linux-gnueabihf`

Hardware Setup
To get temperature readings, the TMP36 temperature sensor must be wired up to the BeagleBone as shown in this student guide (NOTE: this guide was not created by The Defenders): https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/links/files/2022-student-howtos/TMP36TemperatureSensor.pdf
For our project, the sensor must be connected to AIN1.