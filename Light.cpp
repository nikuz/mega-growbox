#include <Arduino.h>
#include <BH1750FVI.h>
#include <Servo.h>

#include "def.h"
#include "Light.h"
#include "AppI2C.h"
#include "Tools.h"

BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
Servo lightKnob;

unsigned long knobDetachAfter = 3L * 1000L; // detach knob servo 3 sec after last attaching
unsigned long knobAttachLastTime = 0;

Light::Light() {}

Light::~Light() {}

// public

void Light::initiate() {
    AppI2C::select(1);
    LightSensor.begin();
    lightKnob.attach(LIGHT_KNOB_SERVO);
    lightKnob.write(0);
}

char *Light::intensity() {
    AppI2C::select(1);
    uint16_t lux = LightSensor.GetLightIntensity();
    char *result = Tools::intToChar(lux);
    return result;
}

void Light::parseSerialCommand(const char *command, const char *param) {
    int value = map(atoi(param), 0, 100, 0, 180); // from percents to degree
    if (strcmp(command, "knob") == 0) {
        if (lightKnob.read() != value) {
            lightKnob.attach(LIGHT_KNOB_SERVO);
            lightKnob.write(value);
            knobAttachLastTime = millis();
        }
    }
}

void Light::checkKnobPosition() {
    if (lightKnob.attached() && millis() > knobAttachLastTime + knobDetachAfter) {
        lightKnob.detach();
    }
}
