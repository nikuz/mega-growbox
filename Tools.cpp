#include <Arduino.h>

#include "Tools.h"

Tools::Tools() {}

Tools::~Tools() {}

bool Tools::timerCheck(int interval, unsigned long lastInitiate) {
    unsigned long now = millis();
    return (interval * 1000L) < now && now - (interval * 1000L) > lastInitiate;
}

uint8_t Tools::StringToUint8(const char *pString) {
    uint8_t value = 0;

    // skip leading 0 and spaces
    while ('0' == *pString || *pString == ' ') {
        pString++;
    }

    // calculate number until we hit non-numeral char
    while ('0' <= *pString && *pString <= '9') {
        value *= 10;
        value += *pString - '0';
        pString++;
    }
    return value;
}

char *Tools::intToChar(unsigned int value) {
    static char result[5];
    int strLength = 1;
    if (value > 9) {
        strLength = 2;
    } else if (value > 99) {
        strLength = 3;
    } else if (value > 999) {
        strLength = 4;
    } else if (value > 9999) {
        strLength = 5;
    }
    dtostrf(value, strLength, 0, result);

    return result;
}
