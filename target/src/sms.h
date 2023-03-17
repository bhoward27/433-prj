// TODO: Add explanation for file.
#ifndef SMS_H_
#define SMS_H_

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include <iostream>

#include "twilio/config.h"
#include "twilio/twilio.h"
#include "shutdown_manager.h"

class Sms {
    public:
        const std::string defaultToPhoneNumber = twilio::toPhoneNumber;
        const std::string shutdownMessage = "!SHUTDOWN!";

        Sms(ShutdownManager* shutdownManager)
        {
            if (shutdownManager == nullptr) {
                std::invalid_argument("shutdownManager = nullptr");
            }
            this->shutdownManager = shutdownManager;

            thread = std::thread([this] {run();});
        }

        ~Sms()
        {
            thread.join();
        }

        /**
         * This should only be called once, before program shutdown. Whichever class/module is responsible for calling
         * ShutdownManager::requestShutdown() should call this method once immediately afterwards.
         *
         * This method is neccessary, as the thread may have fallen asleep waiting for a new message to be added to the
         * queue and thus be holding up the shutdown procedure.
         */
        void wakeUpForShutdown()
        {
            queueMessage(shutdownMessage);
        }

        void queueMessage(std::string message)
        {
            lock.lock();
            {
                messages.push(message);
                cond_var.notify_one();
            }
            lock.unlock();
        }

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

        void run()
        {
            while (!shutdownManager->isShutdownRequested()) {
                std::unique_lock<std::mutex> unique_lock(lock);
                // Wait for new messages to be queued.
                cond_var.wait(unique_lock, [this] {return !messages.empty();});
                // NOTE: conv_var.wait() has acquired the lock for us, so it's okay to access messages queue.
                bool isEmpty = messages.empty();
                lock.unlock();

                // Process all queued messages, one by one.
                while (!isEmpty) {
                    // Take a message off the queue.
                    std::string message;
                    lock.lock();
                    {
                        message = messages.front();
                        messages.pop();
                    }
                    lock.unlock();

                    if (message == shutdownMessage && shutdownManager->isShutdownRequested()) return;

                    // Send the message.
                    send(message);

                    lock.lock();
                    {
                        isEmpty = messages.empty();
                    }
                    lock.unlock();
                }
            }
        }

        int send(std::string message)
        {
            // TODO: Improve.

            // CITATION: This code is based on code from https://github.com/TwilioDevEd/twilio_cpp_demo.git.
            // See here for the tutorial related to the demo:
            // https://www.twilio.com/docs/sms/tutorials/how-to-send-sms-messages-cpp?code-sample=code-using-the-twilio-rest-api-from-c&code-language=cc&code-sdk-version=default

            std::string response;
            bool verbose = true;
            std::string picture_url = "";

            auto twilio = std::make_shared<twilio::Twilio>(
                accoundSid,
                authToken
            );

            bool message_success = twilio->send_message(
                    toPhoneNumber,
                    fromPhoneNumber,
                    message,
                    response,
                    picture_url,
                    verbose
            );

            // Report success or failure
            if (!message_success) {
                    if (verbose) {
                            std::cout << "Message send failed." << std::endl;
                            if (!response.empty()) {
                                    std::cout << "Response:" << std::endl
                                            << response << std::endl;
                            }
                    }
                    return -1;
            } else if (verbose) {
                    std::cout << "SMS sent successfully!" << std::endl;
                    std::cout << "Response:" << std::endl << response
                            << std::endl;
            }

            return 0;
        }
};
#endif