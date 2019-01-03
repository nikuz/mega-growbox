#ifndef Light_h
#define Light_h

#include <Arduino.h>

class Light {
public:
    Light();

    ~Light();

    static void initiate();

    static char *intensity();

    static void parseSerialCommand(const char *command, const char *param);

    static void checkKnobPosition();
};

#endif /* Light_h */