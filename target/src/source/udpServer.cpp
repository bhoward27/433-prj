// Modified code provided By Brian Fraser, Modified from Linux Programming Unleashed (book)

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <netdb.h>
#include <cstring>			// for strncmp()
#include <unistd.h>			// for close()
#include <ctype.h>
#include <string>
#include <exception>
#include <queue>
#include <mutex>
#include <sstream>

#include "udpServer.h"
#include "waterLevelSensor.h"
#include "heat_sampler.h"
#include "notifier.h"

#define MSG_MAX_LEN 1500
#define PORT        12345
#define READING_MAX_LEN 8
#define MAX_READINGS_PER_PACKET 210
#define MAX_SIZE_HISTORY_NUM_BUFFER 5
#define LENGTH_OF_GET_COMMAND 4
#define MAX_READINGS_PER_LINE 20
#define UPTIME_FILE "/proc/uptime"

static pthread_t samplerId;
static int socketDescriptor;
static ShutdownManager* shutdownManager;
static std::queue<std::string> alerts;
static std::mutex alertLock;
static HeatSampler* heatSampler;
static Notifier* notifier;

static std::string getAlerts();

static void *updServerThread(void *args)
{
	while (1) {
		// Get the data (blocking)
		// Will change sin (the address) to be the address of the client.
		// Note: sin passes information in and out of call!
		struct sockaddr_in sinRemote;
		unsigned int sin_len = sizeof(sinRemote);
		char messageRx[MSG_MAX_LEN];

		// Pass buffer size - 1 for max # bytes so room for the null (string data)
		int bytesRx = recvfrom(socketDescriptor,
			messageRx, MSG_MAX_LEN - 1, 0,
			(struct sockaddr *) &sinRemote, &sin_len);


		// Make it null terminated (so string functions work)
		// - recvfrom given max size - 1, so there is always room for the null
		messageRx[bytesRx] = 0;

		// Checks if the command matches any valid commands and returns an unknown command message if not
		if (strncmp(messageRx, "terminate", strlen("terminate")) == 0) {
			char messageTx[MSG_MAX_LEN];
			sprintf(messageTx, "Program terminating.\n");
			shutdownManager->requestShutdown();
			notifier->wakeUpSmsForShutdown();

			sin_len = sizeof(sinRemote);
			sendto( socketDescriptor,
				messageTx, strlen(messageTx),
				0,
				(struct sockaddr *) &sinRemote, sin_len);
			break;
		}
		else if (strncmp(messageRx, "update", strlen("update")) == 0) {
			std::stringstream stream;
			stream << "update "
				   << WaterLevelSensor_getVoltage1Reading(notifier) << " "
				   << heatSampler->getMeanTemperature() << " "
				   << getAlerts();

			char messageTx[MSG_MAX_LEN];
			sprintf(messageTx, "%s", stream.str().c_str());

			sin_len = sizeof(sinRemote);
			sendto( socketDescriptor,
				messageTx, strlen(messageTx),
				0,
				(struct sockaddr *) &sinRemote, sin_len);
		}
		else if (strncmp(messageRx, "panLeft", strlen("panLeft")) == 0) {
			// Insert panning right code here
			// Send message "stop panning" if the user has gone over the min or max pan
			char str[1024];
			sprintf(str, "panning left");
			char messageTx[MSG_MAX_LEN];
			sprintf(messageTx, "%s", str);

			sin_len = sizeof(sinRemote);
			sendto( socketDescriptor,
				messageTx, strlen(messageTx),
				0,
				(struct sockaddr *) &sinRemote, sin_len);

		}
		else if (strncmp(messageRx, "panRight", strlen("panRight")) == 0) {
			// Insert panning right code here
			// Send message "stop panning" if the user has gone over the min or max pan
			char str[1024];
			sprintf(str, "panning right");
			char messageTx[MSG_MAX_LEN];
			sprintf(messageTx, "%s", str);

			sin_len = sizeof(sinRemote);
			sendto( socketDescriptor,
				messageTx, strlen(messageTx),
				0,
				(struct sockaddr *) &sinRemote, sin_len);

		}
		else {
			char messageTx[MSG_MAX_LEN];
			sprintf(messageTx, "Unknown command\n");

			sin_len = sizeof(sinRemote);
			sendto( socketDescriptor,
				messageTx, strlen(messageTx),
				0,
				(struct sockaddr *) &sinRemote, sin_len);
		}
	}

	// Close
	close(socketDescriptor);

	return 0;
}

static std::string getAlerts()
{
	std::string allAlerts = "";

	alertLock.lock();
	{
		while (!alerts.empty()) {
			std::string alert = alerts.front();
			alerts.pop();
			allAlerts += alert;
		}
	}
	alertLock.unlock();

	return allAlerts;
}

void UpdServer_queueAlert(std::string alert)
{
	alertLock.lock();
	{
		alerts.push(alert);
	}
	alertLock.unlock();
}

void UdpServer_initialize(ShutdownManager* shutdownManagerArg, HeatSampler* heatSamplerArg, Notifier* notifierArg)
{
	shutdownManager = shutdownManagerArg;
	heatSampler = heatSamplerArg;
	notifier = notifierArg;

	// Address
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;                   // Connection may be from network
	sin.sin_addr.s_addr = htonl(INADDR_ANY);    // Host to Network long
	sin.sin_port = htons(PORT);                 // Host to Network short

	// Create the socket for UDP
	socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);

	// Bind the socket to the port (PORT) that we specify
	bind (socketDescriptor, (struct sockaddr*) &sin, sizeof(sin));
    // Check for errors (-1)

    pthread_create(&samplerId, NULL, &updServerThread, NULL);
}

void UdpServer_cleanup(void)
{
    pthread_join(samplerId, NULL);
}