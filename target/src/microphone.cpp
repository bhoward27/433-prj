#include "microphone.h"


Microphone::Microphone() : ain(analogInputNum) {}

int16 Microphone::read()
{
    return ain.read();
}