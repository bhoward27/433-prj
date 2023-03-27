/**
 * This file provides the Sms class, which uses the Twilio online SMS service to send text messages.
 *
 * To send a text, call the queueMessage() method.
 */
#ifndef SMS_H_
#define SMS_H_

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

#include "twilio/config.h"
#include "shutdown_manager.h"

class Sms {
    public:
        const std::string badToPhoneNumber = "+10123456789";
        const std::string defaultToPhoneNumber = twilio::toPhoneNumber;
        const std::string shutdownMessage = "!SHUTDOWN!";
        const std::string updateHeader = "**** Sms ****\n";

        /**
         * Starts the Sms thread, which will wake up when queueMessage() is called and sleep again after all queued
         * messages are sent.
         *
         * @param shutdownManager a pointer to the program's ShutdownManager, which will control when the Sms
         * thread stops.
         * @param printUpdates set to true if you want updates printed to the console saying whether messages were sent
         * succesfully.
         */
        Sms(ShutdownManager* shutdownManager, bool printUpdates = false);

        /// Block until shutdownManager->requestShutdown() is called somewhere in the program.
        ~Sms();

        /**
         * This should only be called once, before program shutdown. Whichever class/module is responsible for calling
         * ShutdownManager::requestShutdown() should call this method once immediately afterwards.
         *
         * This method is neccessary, as the thread may have fallen asleep waiting for a new message to be added to the
         * queue and thus be holding up the shutdown procedure.
         */
        void wakeUpForShutdown();

        /// Queue a message to be sent via SMS.
        void queueMessage(std::string message);

    private:
        const std::string accoundSid = twilio::accountSid;
        const std::string authToken = twilio::authToken;
        const std::string fromPhoneNumber = twilio::fromPhoneNumber;
        std::string toPhoneNumber = defaultToPhoneNumber;
        ShutdownManager* shutdownManager;
        std::thread thread;
        std::queue<std::string> messages;
        std::mutex lock; // Lock for the messages queue.
        std::condition_variable cond_var; // For the messages queue.
        bool printUpdates;

        /// Run thread that processes and sends off any new messages that are added to messages queue.
        void run();

        /**
         *  Blocking call which sends message using the Twilio online SMS service.
         *  Returns true if message was sent successfully and false otherwise.
         */
        bool send(std::string message);
};
#endif