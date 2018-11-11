#ifndef Tools_h
#define Tools_h

#include <Arduino.h>

class Tools {
public:
    Tools();

    ~Tools();

    static bool timerCheck(int interval, unsigned long lastInitiate);
    static uint8_t StringToUint8(const char *pString);
};

#endif /* Tools_h */