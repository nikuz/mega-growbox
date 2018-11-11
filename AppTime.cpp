#include <Arduino.h>
#include <RtcDS3231.h>
#include <Wire.h>

#include "def.h"
#include "AppTime.h"
#include "Tools.h"

RtcDS3231 <TwoWire> Rtc(Wire);

bool rtcBatteryAlive = true;
static const char months[][4] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

AppTime::AppTime() {}

AppTime::~AppTime() {}

void AppTime::RTCBegin() {
    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    if (!Rtc.IsDateTimeValid()) {
        Rtc.SetDateTime(compiled);
        Serial.println("RTC lost confidence in the DateTime!");
    }
    if (!Rtc.GetIsRunning()) {
        Rtc.SetIsRunning(true);
        Serial.println("RTC was not actively running, starting now");
    }
    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) {
        Rtc.SetDateTime(compiled);
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
    }

    // never assume the Rtc was last configured by you, so
    // just clear them to your needed state
    Rtc.Enable32kHzPin(false);
    Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
}

char *AppTime::RTCGetTemperature() {
    RtcTemperature rtcTemp = Rtc.GetTemperature();
    static char temperatureStr[2];
    float rtcTempFloat = rtcTemp.AsFloatDegC();
    int strLength = 1;
    if (rtcTempFloat > 10) {
        strLength = 2;
    }
    dtostrf(rtcTempFloat, strLength, 0, temperatureStr);

    return temperatureStr;
}

char *AppTime::RTCBattery() {
    return rtcBatteryAlive ? "1" : "0";
}

bool AppTime::RTCIsDateTimeValid() {
    const bool isValid = Rtc.IsDateTimeValid();

    if (!isValid) {
        rtcBatteryAlive = false;
    } else {
        rtcBatteryAlive = true;
    }

    return isValid;
}

char *AppTime::RTCGetCurrentTime() {
    RtcDateTime rtcTime = Rtc.GetDateTime();
    AppTime::RTCIsDateTimeValid();

    static char timeStr[20];
    snprintf_P(
            timeStr,
            sizeof timeStr,
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            rtcTime.Month(),
            rtcTime.Day(),
            rtcTime.Year(),
            rtcTime.Hour(),
            rtcTime.Minute(),
            rtcTime.Second()
    );

    return timeStr;
}

void AppTime::RTCDateTimeUpdate(const char *command, const char *param) {
    // 10/10/2018 00:09:21
    if (strcmp(command, "time") == 0) {
        char *string, *found, *time;
        char date[15];
        string = strdup(param);
        int i = 0;

        while((found = strsep(&string, " ")) != NULL) {
            if (i == 0) {
                char *substring, *subfound;
                substring = strdup(found);
                uint8_t month;
                char *day, *year;
                int dateI = 0;
                while((subfound = strsep(&substring, "/")) != NULL) {
                    switch (dateI) {
                        case 0:
                            month = Tools::StringToUint8(subfound);
                            break;
                        case 1:
                            day = Tools::StringToUint8(subfound);
                            break;
                        case 2:
                            year = subfound;
                            break;
                    }
                    dateI++;
                }
                sprintf(
                        date,
                        "%.3s%3d %.4s",
                        months[month - 1],
                        day,
                        year
                );
                free(substring);
            } else {
                time = found;
            }
            i++;
        }
        free(string);

        RtcDateTime ntpDateTime = RtcDateTime(date, time);
        Rtc.SetDateTime(ntpDateTime);
    }
}