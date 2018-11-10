#include <Arduino.h>

#include "Tools.h"

Tools::Tools() {}

Tools::~Tools() {}

bool Tools::timerCheck(int interval, unsigned long lastInitiate) {
    unsigned long now = millis();
    return (interval * 1000L) < now && now - (interval * 1000L) > lastInitiate;
}
