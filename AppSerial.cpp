#include <Arduino.h>

#include "AppSerial.h"

static char command[10];
static char param[20];
static char chunk;
static byte i = 0;
static boolean delimiterPassed = false;
static boolean gotCommand = false;

AppSerial::AppSerial() {}

AppSerial::~AppSerial() {}

SerialFrame AppSerial::getFrame() {
    delimiterPassed = false;
    gotCommand = false;
    i = 0;

    if (Serial1.available() > 0) {
        memset(command, 0, sizeof(command));
        memset(param, 0, sizeof(param));
    }

    while (Serial1.available() > 0 && gotCommand == false) {
        delay(1);
        chunk = Serial1.read();
        if (chunk != frameDelimiter && chunk != frameEndMarker) {
            if (delimiterPassed) {
                param[i] = chunk;
            } else {
                command[i] = chunk;
            }
            i++;
        } else if (chunk == frameDelimiter) {
            command[i] = '\0'; // terminate the command
            i = 0;
            delimiterPassed = true;
        } else if (chunk == frameEndMarker) {
            if (delimiterPassed) {
                param[i] = '\0'; // terminate the param
            }
            gotCommand = true;
            i = 0;
        }
    }

    if (gotCommand) {
        Serial.print(command);
        Serial.print(frameDelimiter);
        Serial.println(param);

        return SerialFrame(command, param);
    }

    return SerialFrame("", "");
}

void AppSerial::sendFrame(SerialFrame *serialFrame) {
    delay(1);
    Serial1.write(serialFrame->command);
    Serial1.write(serialFrame->delimiter);
    Serial1.write(serialFrame->param);
    Serial1.write(serialFrame->endMarker);
    Serial1.flush();
}
