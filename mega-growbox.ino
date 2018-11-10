#include "Relay.h"
#include "AppSerial.h"
#include "AppTime.h"
#include "Sensor.h"
#include "Tools.h"

int DHTPReadInterval = 1;  // read sensor once in one second
unsigned long DHTPReadLastTime = millis();

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    Serial1.begin(115200);
    while (!Serial1) {
        ;
    }

    Relay::initiate();
    AppTime::RTCBegin();
    AppTime::RTCGetCurrentTime();
}

void loop() {

    SerialFrame serialFrame = AppSerial::getFrame();
    if (strcmp(serialFrame.command, "") != 0) {
        Relay::parseSerialCommand(serialFrame.command, serialFrame.param);
    }

    // Timers
    if (Tools::timerCheck(DHTPReadInterval, DHTPReadLastTime)) {
        Sensor::readDHT();
        Sensor::temperatureGet();
        Sensor::humidityGet();
        DHTPReadLastTime = millis();
    }
}
