/**
 * This file provides the Notifier class. It is used to send notifications to the user regarding the occurrence of
 * certain events. Notifications will be sent to the user's cell phone via SMS, and to the web server via UDP.
 * TODO: Sending via UDP has not been implemented yet.
 *
 * Example usage: Suppose the temperature has gotten too hot. The programmer should then call
 * notifer->raiseEvent(Event::extremeHeat, ...). After the temperature has cooled down, call
 * notifer->clearEvent(Event::extremeHeat, ...).
 */
#ifndef NOTIFIER_H_
#define NOTIFIER_H_

#include <unordered_map>
#include <string>

#include "sms.h"
#include "shutdown_manager.h"

/// Different events the user might want to be notified about.
enum class Event {
    extremeHeat,
    extremeCold,
    fireAlarmDetected,
    flood
    // NOTE: Add more events here as needed, then add it to eventInfoMap (Ctrl/Cmd-F on this file to find it).
};

struct EventInfo {
    // Indicates whether a particular event has been raised or not.
    bool isRaised;

    // The name of the event, which will appear in notifications.
    std::string name;
};

class Notifier {
    public:
        // This appears at the top of SMS notifications.
        const std::string smsAppHeader = "**** BBG Alert ****\n";

        const std::string smsDatePrefix = "\n(";
        const std::string smsDateSuffix = ")";

        const std::string updateHeader = "**** Notifier ****\n";

        /**
         * Constructor.
         *
         * @param shutdownManager a pointer to the program's ShutdownManager, which will control when Sms's
         * thread stops.
         * @param printUpdates set to true if you want updates printed to the console regarding event status and
         * sending of SMS messages
         */
        Notifier(ShutdownManager* shutdownManager, bool printUpdates = false);

        /**
         * Mark event as raised, then, if the event wasn't already raised, notify the user.
         * Not thread-safe, but that's okay, as long as there aren't multiple threads trying to raise/clear the
         * same event.
         *
         * @param event the event to be raised.
         * @param messageBody the body of the message that will appear in the notification. This should be used to
         * include further details of the event (e.g., if the event was extremeHeat, include the current temperature
         * in messageBody).
         */
        void raiseEvent(Event event, std::string messageBody);

        /**
         * Mark event as not raised, then, if the event was raised before, notify the user.
         * Not thread-safe, but that's okay, as long as there aren't multiple threads trying to raise/clear the
         * same event.
         *
         * @param event the event to be cleared/lowered/not raised.
         * @param messageBody optional, the message body that will appear in the notification. Used to provide extra
         * details related to why the event has ended.
         */
        void clearEvent(Event event, std::string messageBody = "");

        /**
         * This should only be called once, before program shutdown. Whichever class/module is responsible for calling
         * ShutdownManager::requestShutdown() should call this method once immediately afterwards.
         *
         * This method is neccessary, as the Sms thread may have fallen asleep waiting for a new message to be added to
         * the queue and thus be holding up the shutdown procedure.
         */
        void wakeUpSmsForShutdown();

    private:
        std::unordered_map<Event, EventInfo> eventInfoMap = {
            {Event::extremeHeat,       {false, "Extreme Heat"}},
            {Event::extremeCold,       {false, "Extreme Cold"}},
            {Event::fireAlarmDetected, {false, "Fire Alarm"}},
            {Event::flood,             {false, "Flood"}}
            // NOTE: Add a new entry here when adding a new event.
            // If you get an out_of_range error after calling
            // raise/clearEvent(), you probably forgot to do this.
        };

        Sms sms;
        bool printUpdates;

        /**
         * Notify the user that an event has occurred or ended. Notifications are sent via SMS to the user's cell
         * phone and via UDP to the web server.
         * TODO: Sending notifications to the web server has not yet been implemented!
         *
         * @param event the event to be notified about.
         * @param raise boolean indicating whether the event was just raised or cleared. The notification's content will
         * reflect this option.
         * @param messageBody additional details relating to why the event was raised or cleared. This string appear in
         * the notification. Set to null string if no additional details are needed.
         */
        void notify(Event event, bool raise, std::string messageBody);
};

#endif