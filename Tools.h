#ifndef Tools_h
#define Tools_h

#include <Arduino.h>

class Tools {
public:
    Tools();

    ~Tools();

    static bool timerCheck(int interval, unsigned long lastInitiate);
};

#endif /* Tools_h */