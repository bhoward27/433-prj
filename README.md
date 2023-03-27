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
To get temperature readings, the TMP36 temperature sensor must be wired up to the BeagleBone with a voltage divider setup, with the sensor's Vout connected to AIN2 on the ADC. Ask Ben if you don't know how to wire it up.

Building the App on the Host Machine
Ensure NFS is set up with the BBG. Then, on the host:
`cd target/src`
`make`

Running the App on the BeagleBone
Navigate to the exported NFS myApp folder. Then:
`./a.out`