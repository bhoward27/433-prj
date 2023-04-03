#include <stdexcept>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "notifier.h"
#include "utils.h"

Notifier::Notifier(ShutdownManager* shutdownManager, bool printUpdates) : sms(shutdownManager, printUpdates),
                                                                          printUpdates(printUpdates)
{ /* Deliberately empty. */}

void Notifier::raiseEvent(Event event, std::string messageBody)
{
    try {
        // If event was not already raised.
        if (!eventInfoMap.at(event).isRaised) {
            eventInfoMap[event].isRaised = true;
            notify(event, true, messageBody);
            if (printUpdates) {
                std::cout << updateHeader
                          << "Raised " << eventInfoMap[event].name << " Event.\n\n";
            }
        }
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("Bad key: Tried to access an event that does not exist in eventInfoMap.");
    }
}

void Notifier::clearEvent(Event event, std::string messageBody)
{
    try {
        // If event is raised.
        if (eventInfoMap.at(event).isRaised) {
            eventInfoMap[event].isRaised = false;
            notify(event, false, messageBody);
            if (printUpdates) {
                std::cout << updateHeader
                          << "Cleared " << eventInfoMap[event].name << " Event.\n\n";
            }
        }
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("Bad key: Tried to access an event that does not exist in eventInfoMap.");
    }
}

void Notifier::wakeUpSmsForShutdown()
{
    sms.wakeUpForShutdown();
}

void Notifier::notify(Event event, bool raise, std::string messageBody)
{
    // CITATIONS for how to get and format system time:
    // - https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
    // - https://stackoverflow.com/a/16358111
    // - https://en.cppreference.com/w/cpp/io/manip/put_time
    time_t now = time(0);
    tm* localNow = localtime(&now);

    // Format date and time as a string. E.g., "Mar. 25, 2:05 PM". This will be appended to the SMS message.
    std::stringstream dateStream;
    dateStream << std::put_time(localNow, "%b. %d, %I:%M %p");

    std::string smsMessage;
    if (raise) {
        smsMessage = smsAppHeader + toUpper(eventInfoMap[event].name) + ": " + messageBody +
                     smsDatePrefix + dateStream.str() + smsDateSuffix;
    }
    else {
        if (messageBody != "") {
            // Add a space in front.
            messageBody = " " + messageBody;
        }
        smsMessage = smsAppHeader + eventInfoMap[event].name + " Event ended." + messageBody +
                     smsDatePrefix + dateStream.str() + smsDateSuffix;
    }

    sms.queueMessage(smsMessage);

    // TODO: Send appropriate message to web server.
}