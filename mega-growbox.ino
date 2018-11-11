#include "Relay.h"
#include "AppSerial.h"
#include "AppTime.h"
#include "Sensor.h"
#include "Tools.h"

int TimeReadInterval = 1;  // read sensor once in two seconds
unsigned long TimeReadLastTime = millis();

int DHTPReadInterval = 2;  // read sensor once in two seconds
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
}

void loop() {
    SerialFrame serialFrame = AppSerial::getFrame();
    if (strcmp(serialFrame.command, "") != 0) {
        bool performRelayCommand = Relay::parseSerialCommand(serialFrame.command, serialFrame.param);
        if (performRelayCommand) {
            AppSerial::sendFrame(&serialFrame);
        }
    }

    // RTC time and temperature
    if (Tools::timerCheck(TimeReadInterval, TimeReadLastTime)) {
        const char timeStr[20];
        AppTime::RTCGetCurrentTime(timeStr);
        SerialFrame timeFrame = SerialFrame("time", timeStr);
        AppSerial::sendFrame(&timeFrame);

        const char timeTempStr[2];
        AppTime::RTCGetTemperature(timeTempStr);
        SerialFrame timeTemperatureFrame = SerialFrame("ttemp", timeTempStr);
        AppSerial::sendFrame(&timeTemperatureFrame);

        TimeReadLastTime = millis();
    }
    // DHT temperature and humidity
    if (Tools::timerCheck(DHTPReadInterval, DHTPReadLastTime)) {
        Sensor::readDHT();

        const char tempStr[2];
        Sensor::temperatureGet(tempStr);
        SerialFrame temperatureFrame = SerialFrame("temp", tempStr);
        AppSerial::sendFrame(&temperatureFrame);

        const char humStr[2];
        Sensor::humidityGet(humStr);
        SerialFrame humidityFrame = SerialFrame("hum", humStr);
        AppSerial::sendFrame(&humidityFrame);

        DHTPReadLastTime = millis();
    }
    //
}
