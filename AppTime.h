#ifndef AppTime_h
#define AppTime_h

#include <Arduino.h>

class AppTime {
public:
    AppTime();

    ~AppTime();

    static void RTCBegin();

    static char *RTCGetTemperature();

    static char *RTCBattery();

    static bool RTCIsDateTimeValid();

    static char *RTCGetCurrentTime();

    static void RTCDateTimeUpdate(const char *date, const char *time);
};

#endif /* AppTime_h */
