# Home Defense System

Directory Structure
There are two main folders: target and host.
target contains all files relevant to code which runs on the target (the BeagleBone Green).
host contains all files relevant to code which runs on the host (Debian PC/VM).
Source code goes into the src folder within the target or host folder.

Dependencies
You will need the g++ cross-compiler to build the code in target/src.
To install it, run this command on your host:
`sudo apt install g++-arm-linux-gnueabihf`