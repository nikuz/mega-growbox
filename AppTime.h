#ifndef AppTime_h
#define AppTime_h

#include <Arduino.h>

class AppTime {
public:
    AppTime();

    ~AppTime();

    static void RTCBegin();

    static void RTCGetTemperature(char *temperatureStr);

    static bool RTCBattery();

    static bool RTCIsDateTimeValid();

    static void RTCGetCurrentTime(char *timeStr);

    static void RTCDateTimeUpdate(const char *date, const char *time);
};

#endif /* AppTime_h */
