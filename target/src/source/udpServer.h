// Module allows you to initialize the udpserver in a thread which can reply to commands
// The server will provide access to the following commands
// count, length, history, get #, dips, and stop
// the stop command is how the whole application will stop and clean up other modules

#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <pthread.h>
#include <string>

// Initializes the udpServer and allows it to take commands
void UdpServer_initialize();

// Cleans up and closes the udpServer
void UdpServer_cleanup(void);

// Queue an alert to be sent to the web server.
void UpdServer_queueAlert(std::string alert);

#endif