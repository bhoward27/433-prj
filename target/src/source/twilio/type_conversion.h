/// Twilio SMS code -- String conversion functions.

// CITATION: This code was cloned from https://github.com/TwilioDevEd/twilio_cpp_demo.git.
// See here for the tutorial related to the demo:
// https://www.twilio.com/docs/sms/tutorials/how-to-send-sms-messages-cpp?code-sample=code-using-the-twilio-rest-api-from-c&code-language=cc&code-sdk-version=default
#ifndef TYPE_CONVERSION_H_
#define TYPE_CONVERSION_H_

#include <locale>
#include <codecvt>
#include <string>

// Given a UTF-8 encoded string return a new UCS-2 string.
inline std::u16string
utf8_to_ucs2(std::string const& input)
{
        std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> convert;
        try {
                return convert.from_bytes(input);
        } catch(const std::range_error& e) {
                throw std::range_error(
                        "Failed UCS-2 conversion of message body.  Check all "
                        "characters are valid GSM-7, GSM 8-bit text, or UCS-2 "
                        "characters."
                );
        }
}

// Given a UCS-2 string return a new UTF-8 encoded string.
inline std::string
ucs2_to_utf8(std::u16string const& input)
{
        std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> convert;
        return convert.to_bytes(input);
}

#endif