#ifndef AppSerial_h
#define AppSerial_h

#include <Arduino.h>

struct SerialFrame {
    const char *command;
    const char *param;

    SerialFrame() {}
    SerialFrame(const char *_command, const char *_param) : command(_command), param(_param) {}
};

class AppSerial {
public:
    AppSerial();

    ~AppSerial();

    static SerialFrame getFrame();
};

#endif /* AppSerial_h */