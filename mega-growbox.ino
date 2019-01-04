#include "Relay.h"
#include "AppSerial.h"
#include "AppI2C.h"
#include "AppTime.h"
#include "Sensor.h"
#include "Light.h"
#include "Tools.h"
#include "def.h"

int TimeReadInterval = 1;  // read sensor once in two seconds
unsigned long TimeReadLastTime = millis();

int SensorsReadInterval = 2;  // read sensor once in two seconds
unsigned long SensorsReadLastTime = millis();

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    Serial.print("Version: ");
    Serial.print(VERSION_MARKER);
    Serial.println(VERSION);
    Serial.println("");

    Serial1.begin(115200);
    while (!Serial1) {
        ;
    }

    AppI2C::initiate();
    AppI2C::scan();
    Relay::initiate();
    Sensor::initiate();
    Light::initiate();
    AppTime::RTCBegin();
}

void loop() {
    SerialFrame serialFrame = AppSerial::getFrame();
    if (strcmp(serialFrame.command, "") != 0) {
        // relay
        bool performRelayCommand = Relay::parseSerialCommand(serialFrame.command, serialFrame.param);
        if (performRelayCommand) {
            AppSerial::sendFrame(&serialFrame);
        }
        Light::parseSerialCommand(serialFrame.command, serialFrame.param);
        // sync RTC time by NTP
        AppTime::RTCDateTimeUpdate(serialFrame.command, serialFrame.param);
//        // serial speed test
//        if (strcmp(serialFrame.command, "test") == 0) {
//            unsigned long testStart = millis();
//            SerialFrame testFirstFrame = SerialFrame("test", "first");
//            AppSerial::sendFrame(&testFirstFrame);
//            while (millis() - testStart < 1000) {
//                unsigned long val = millis() - testStart;
//                char *testStr = Tools::intToChar(val);
//                SerialFrame testFrame = SerialFrame("test", testStr);
//                AppSerial::sendFrame(&testFrame);
//            }
//            SerialFrame testLastFrame = SerialFrame("test", "last");
//            AppSerial::sendFrame(&testLastFrame);
//        }
    }

    // RTC time and temperature
    if (Tools::timerCheck(TimeReadInterval, TimeReadLastTime)) {
        const char *timeParam = AppTime::RTCGetCurrentTime();
        SerialFrame timeFrame = SerialFrame("time", timeParam);
        AppSerial::sendFrame(&timeFrame);

        const char *timeTempParam = AppTime::RTCGetTemperature();
        SerialFrame timeTemperatureFrame = SerialFrame("ttemp", timeTempParam);
        AppSerial::sendFrame(&timeTemperatureFrame);

        const char *timeBatteryParam = AppTime::RTCBattery();
        SerialFrame timeBatteryFrame = SerialFrame("tbtr", timeBatteryParam);
        AppSerial::sendFrame(&timeBatteryFrame);

        TimeReadLastTime = millis();
    }
    // sensors
    if (Tools::timerCheck(SensorsReadInterval, SensorsReadLastTime)) {
        Sensor::readDHT();

        const char *tempParam = Sensor::temperatureGet();
        SerialFrame temperatureFrame = SerialFrame("temp", tempParam);
        AppSerial::sendFrame(&temperatureFrame);

        const char *humParam = Sensor::humidityGet();
        SerialFrame humidityFrame = SerialFrame("hum", humParam);
        AppSerial::sendFrame(&humidityFrame);

        const char *humWaterParam = Sensor::humidityHasWater();
        SerialFrame humidityWaterFrame = SerialFrame("humw", humWaterParam);
        AppSerial::sendFrame(&humidityWaterFrame);

        const char *wateringWaterParam = Sensor::wateringHasWater();
        SerialFrame wateringWaterFrame = SerialFrame("water", wateringWaterParam);
        AppSerial::sendFrame(&wateringWaterFrame);

        int soilSensors[] = {SOIL_SENSOR_1, SOIL_SENSOR_2, SOIL_SENSOR_3, SOIL_SENSOR_4};
        int soilSensorsCounts = *(&soilSensors + 1) - soilSensors;
        for (int i = 0; i < soilSensorsCounts; i++) {
            const char command[] = "soil";
            const char *commandEnd = Tools::intToChar(i + 1);
            strcat(command, commandEnd);
            const char *soilHumidityParam = Sensor::getSoilMoisture(soilSensors[i]);
            SerialFrame soilHumidityFrame = SerialFrame(command, soilHumidityParam);
            AppSerial::sendFrame(&soilHumidityFrame);
        }

        const char *lightIntensityParam = Light::intensity();
        SerialFrame lightIntensityFrame = SerialFrame("light", lightIntensityParam);
        AppSerial::sendFrame(&lightIntensityFrame);

        const char *doorIsOpenParam = Sensor::doorIsOpen();
        SerialFrame doorIsOpenParamFrame = SerialFrame("door", doorIsOpenParam);
        AppSerial::sendFrame(&doorIsOpenParamFrame);

        int rainSensors[] = {RAIN_SENSOR_1, RAIN_SENSOR_2, RAIN_SENSOR_3, RAIN_SENSOR_4};
        int rainSensorsCounts = *(&rainSensors + 1) - rainSensors;
        for (int i = 0; i < rainSensorsCounts; i++) {
            const char command[] = "rain";
            const char *commandEnd = Tools::intToChar(i + 1);
            strcat(command, commandEnd);
            const char *rainParam = Sensor::getRainStatus(rainSensors[i]);
            SerialFrame rainFrame = SerialFrame(command, rainParam);
            AppSerial::sendFrame(&rainFrame);
        }

        SensorsReadLastTime = millis();
    }
    //

    Light::checkKnobPosition();
}
