#include <Arduino.h>

#include "AppSerial.h"

static char command[5];
static char param[15];
static char delimiter = ':';
static char endMarker = '\n';
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
        if (chunk != delimiter && chunk != endMarker) {
            if (delimiterPassed) {
                param[i] = chunk;
            } else {
                command[i] = chunk;
            }
            i++;
        } else if (chunk == delimiter) {
            command[i] = '\0'; // terminate the command
            i = 0;
            delimiterPassed = true;
        } else if (chunk == endMarker) {
            if (delimiterPassed) {
                param[i] = '\0'; // terminate the param
            }
            gotCommand = true;
            i = 0;
        }
    }

    if (gotCommand) {
        Serial.print(command);
        Serial.print(delimiter);
        Serial.println(param);

        return SerialFrame(command, param);
    }

    return SerialFrame("", "");
}
