#include <iostream>
#include <string>

#include "heat_sampler.h"
#include "twilio/twilio.h"
#include "twilio/config.h"

int main() {
    std::cout << "Hello BeagleBone!\n";

    ShutdownManager shutdownManager;

    // TODO: Add back in after wired up.
    // // Sample the temperature at 1 Hz and calculate window average over the last 10 samples.
    // HeatSampler heatSampler(&shutdownManager, 1, 10, true);
    // // Construct like this instead if you want the sampler to not print anything:
    // // HeatSampler heatSampler(&shutdownManager, 1, 10);

    // heatSampler.waitForShutdown();

    // TODO: Remove later. Testing.
    // Initialize variables.
    std::string account_sid = twilio::accountSid;
    std::string auth_token = twilio::authToken;
    std::string to_number = twilio::toPhoneNumber;
    std::string from_number = twilio::fromPhoneNumber;
    std::string message = "hello hello, what have we here?";
    std::string picture_url = "";
    bool verbose = true;

    // Instantiate a twilio object and call send_message
    std::string response;
    auto twilio = std::make_shared<twilio::Twilio>(
        account_sid,
        auth_token
    );

    bool message_success = twilio->send_message(
            to_number,
            from_number,
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

    message_success = twilio->send_message(
            to_number,
            from_number,
            "2",
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
    message_success = twilio->send_message(
            to_number,
            from_number,
            "3",
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