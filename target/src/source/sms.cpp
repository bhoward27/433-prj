#include <iostream>

#include "sms.h"
#include "twilio/twilio.h"

Sms::Sms(ShutdownManager* shutdownManager, bool printUpdates)
{
    if (shutdownManager == nullptr) {
        throw std::invalid_argument("shutdownManager = nullptr");
    }
    this->shutdownManager = shutdownManager;

    if (toPhoneNumber == badToPhoneNumber) {
        throw std::invalid_argument(
            "toPhoneNumber == '" + badToPhoneNumber + "', which indicates that twilio::toPhoneNumber in " +
            "'twilio/config.h' has not been changed to a valid phone number. You should change this constant " +
            "to your personal phone number, then re-compile the application."
        );
    }

    this->printUpdates = printUpdates;

    thread = std::thread([this] {run();});
}

Sms::~Sms()
{
    thread.join();
}

void Sms::wakeUpForShutdown()
{
    queueMessage(shutdownMessage);
}

void Sms::queueMessage(std::string message)
{
    lock.lock();
    {
        messages.push(message);
        cond_var.notify_one();
    }
    lock.unlock();
}

void Sms::run()
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

            // This condition will be true if ShutdownManager::requestShutdown() followed by
            // wakeUpForShutdown() is called.
            if (message == shutdownMessage && shutdownManager->isShutdownRequested()) return;

            send(message);

            lock.lock();
            {
                isEmpty = messages.empty();
            }
            lock.unlock();
        }
    }
}

bool Sms::send(std::string message)
{
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
        if (printUpdates) {
            std::cout << updateHeader;
            std::cout << "Message send failed." << std::endl;
            if (!response.empty()) {
                std::cout << "Response:" << std::endl
                            << response << std::endl;
            }
            std::cout << std::endl;
        }
        return false;
    } else if (printUpdates) {
        std::cout << updateHeader;
        std::cout << "SMS sent successfully!" << std::endl;
        std::cout << "Response:" << std::endl << response << std::endl;
        std::cout << std::endl;
    }

    return true;
}