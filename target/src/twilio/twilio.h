// TODO: Add explanation for the file.
// CITATION: This code was cloned from https://github.com/TwilioDevEd/twilio_cpp_demo.git.
// See here for the tutorial related to the demo:
// https://www.twilio.com/docs/sms/tutorials/how-to-send-sms-messages-cpp?code-sample=code-using-the-twilio-rest-api-from-c&code-language=cc&code-sdk-version=default
#ifndef TWILIO_H_
#define TWILIO_H_

#include <string>
#include "type_conversion.h"

namespace twilio {

class Twilio {
public:
        Twilio(std::string const& account_sid_in,
               std::string const& auth_token_in)
                : account_sid(account_sid_in)
                , auth_token(auth_token_in)
        {}
        // Nothing in destructor
        ~Twilio() = default;

        bool send_message(
                std::string const& to_number,
                std::string const& from_number,
                std::string const& message_body,
                std::string& response,
                std::string const& picture_url = "",
                bool verbose = false
        );

private:
        // Account SID and Auth Token come from the Twilio console.
        // See: https://twilio.com/console for more.

        // Used for the username of the auth header
        std::string const account_sid;
        // Used for the password of the auth header
        std::string const auth_token;

        // Portably ignore curl response
        static size_t _null_write(char *, size_t, size_t, void *);
        // Write curl response to a stringstream
        static size_t _stream_write(char *, size_t, size_t, void *);
};

} // end namespace twilio

#endif