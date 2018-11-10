#include <Arduino.h>
#include <RtcDS3231.h>
#include <Wire.h>

#include "def.h"
#include "AppTime.h"

#define countof(a) (sizeof(a) / sizeof(a[0]))

RtcDS3231 <TwoWire> Rtc(Wire);
bool rtcBatteryIsLive = true;

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

int AppTime::RTCGetTemperature() {
    RtcTemperature rtcTemp = Rtc.GetTemperature();
    const int temperature = (int) rtcTemp.AsFloatDegC();

    Serial.print("RTC temperature: ");
    Serial.println(temperature);

    return temperature;
}

bool AppTime::RTCBattery() {
    Serial.print("RTC battery is alive: ");
    Serial.println(rtcBatteryIsLive ? "True" : "False");

    return rtcBatteryIsLive;
}

bool AppTime::RTCIsDateTimeValid() {
    const bool isValid = Rtc.IsDateTimeValid();

    Serial.print("RTC datetime is valid: ");
    Serial.println(isValid ? "True" : "False");

    return isValid;
}

String AppTime::RTCGetCurrentTime() {
    RtcDateTime rtcTime = Rtc.GetDateTime();

    if (!AppTime::RTCIsDateTimeValid()) {
        rtcBatteryIsLive = false;
    } else {
        rtcBatteryIsLive = true;
    }

    char timeString[20];
    snprintf_P(
            timeString,
            countof(timeString),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            rtcTime.Month(),
            rtcTime.Day(),
            rtcTime.Year(),
            rtcTime.Hour(),
            rtcTime.Minute(),
            rtcTime.Second()
    );

    Serial.print("RTC time: ");
    Serial.println(timeString);

    return timeString;
}

void AppTime::RTCDateTimeUpdate(const char *date, const char *time) {
    // Nov 10 2018 00:09:21
    if (date && time) {
        RtcDateTime ntpDateTime = RtcDateTime(date, time);
        Rtc.SetDateTime(ntpDateTime);

        Serial.print("Update RTC datetime to: ");
        Serial.print(date);
        Serial.print(" ");
        Serial.println(time);
    }
}