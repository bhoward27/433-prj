#ifndef NOTIFIER_H_
#define NOTIFIER_H_

#include <unordered_map>
#include <stdexcept>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

#include "sms.h"
#include "shutdown_manager.h"
#include "utils.h"

enum class Event {
    extremeHeat,
    extremeCold,
    fireAlarmDetected,
    flood
};

struct EventInfo {
    bool isRaised;
    std::string name;
};

class Notifier {
    public:
        const std::string smsAppHeader = "**** BBG Home Alert System ****\n";
        const std::string smsDatePrefix = "\n(";
        const std::string smsDateSuffix = ")";

        Notifier(ShutdownManager* shutdownManager, bool printUpdates = false) : sms(shutdownManager, printUpdates) {}

        // Not thread-safe, but that's okay, as long as there aren't multiple threads trying to raise/clear the
        // same event.
        void raiseEvent(Event event, std::string messageBody)
        {
            // If event was not already raised.
            if (!eventInfoMap[event].isRaised) {
                eventInfoMap[event].isRaised = true;
                notify(event, true, messageBody);
            }
        }

        // Not thread-safe, but that's okay, as long as there aren't multiple threads trying to raise/clear the same
        // event.
        void clearEvent(Event event, std::string messageBody = "")
        {
            // If event is raised.
            if (eventInfoMap[event].isRaised) {
                eventInfoMap[event].isRaised = false;
                notify(event, false, messageBody);
            }
        }

        void wakeUpSmsForShutdown()
        {
            sms.wakeUpForShutdown();
        }

    private:
        std::unordered_map<Event, EventInfo> eventInfoMap = {
            {Event::extremeHeat,       {false, "Extreme Heat"}},
            {Event::extremeCold,       {false, "Extreme Cold"}},
            {Event::fireAlarmDetected, {false, "Fire Alarm"}},
            {Event::flood,             {false, "Flood"}}
        };

        Sms sms;

        void notify(Event event, bool raise, std::string messageBody)
        {
            // CITATION for how to get system time:
            // https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
            time_t now = time(0);
            tm* localNow = localtime(&now);
            // Format time as a string. E.g., "April 2, 14:01"
            std::stringstream dateStream;
            // dateStream << 1 + localNow->tm_mon << " " << localNow->tm_mday << ", "
            //            << 5 + localNow->tm_hour << ":" << 30 + localNow->tm_min;
            // dateStream << std::put_time(localNow, "%d-%m-%Y %H-%M-%S");
            dateStream << std::put_time(localNow, "%b. %d, %I:%M %p");

            if (raise) {
                std::string smsMessage = smsAppHeader +
                                         toUpper(eventInfoMap[event].name) + ": " + messageBody +
                                         smsDatePrefix + dateStream.str() + smsDateSuffix;
                sms.queueMessage(smsMessage);

                // TODO: Send appropriate message to web server.
            }
            else {
                if (messageBody == "") {
                    std::string smsMessage = smsAppHeader + eventInfoMap[event].name + " Event ended." +
                                             smsDatePrefix + dateStream.str() + smsDateSuffix;
                    sms.queueMessage(smsMessage);

                    // TODO: Send appropriate message to web server.
                }
                else {
                    std::string smsMessage = smsAppHeader + eventInfoMap[event].name + " Event ended. " + messageBody +
                                             smsDatePrefix + dateStream.str() + smsDateSuffix;
                    sms.queueMessage(smsMessage);

                    // TODO: Send appropriate message to web server.
                }
            }
        }
};

#endif