#include <Arduino.h>

#include "def.h"
#include "Relay.h"

// RelayItem({pin}, {name}, {highLevelTrigger}) - highLevelTrigger is true by default
static RelayItem relays[] = {
        RelayItem(30, "light"), // 220V
        RelayItem(31, "vent"), // 220V
        RelayItem(32, "humidity"), // 220V
        RelayItem(33, "water"), // 220V
        RelayItem(34, "wind"), // 220V
        RelayItem(35, "free"), // 220V
        RelayItem(36, "s1", false), // 12V
        RelayItem(37, "s2", false), // 12V
        RelayItem(38, "s", false), // 12V
        RelayItem(39, "s4", false), // 12V
        RelayItem(40, "sHumidity", false) // 12V
};

Relay::Relay() {}

Relay::~Relay() {}

// public

void Relay::initiate() {
    int relaysCounts = *(&relays + 1) - relays;
    for (int i = 0; i < relaysCounts; i++) {
        // turn off relays by default
        // not all relays is HIGH level triggered
        if (relays[i].highLevelTrigger) {
            Serial.print("HIGH level trigger: ");
            Serial.println(relays[i].name);
            digitalWrite(relays[i].pin, LOW);
        } else {
            Serial.print("LOW level trigger: ");
            Serial.println(relays[i].name);
            digitalWrite(relays[i].pin, HIGH);
        }
        pinMode(relays[i].pin, OUTPUT);
    }
}

void Relay::parseSerialCommand(const char *command, const char *param) {
    if (strcmp(command, "rOn") == 0) return Relay::on(param);
    if (strcmp(command, "rOf") == 0) return Relay::off(param);
}

// private

void Relay::on(const char *name) {
    RelayItem relayItem = Relay::getRelayPin(name);
    if (relayItem.pin != -1) {
        Serial.print("Relay ON: ");
        Serial.println(relayItem.name);
        if (relayItem.highLevelTrigger) {
            digitalWrite(relayItem.pin, HIGH);
        } else {
            digitalWrite(relayItem.pin, LOW);
        }
    } else {
        Serial.print("Relay doesn't exist: ");
        Serial.println(name);
    }
}

void Relay::off(const char *name) {
    RelayItem relayItem = Relay::getRelayPin(name);
    if (relayItem.name) {
        Serial.print("Relay OFF: ");
        Serial.println(name);
        if (relayItem.highLevelTrigger) {
            digitalWrite(relayItem.pin, LOW);
        } else {
            digitalWrite(relayItem.pin, HIGH);
        }
    } else {
        Serial.print("Relay doesn't exist: ");
        Serial.println(name);
    }
}

RelayItem Relay::getRelayPin(const char *name) {
    int relaysCounts = *(&relays + 1) - relays;
    for (int i = 0; i < relaysCounts; i++) {
        if (strcmp(relays[i].name, name) == 0) {
            return relays[i];
        }
    }

    return RelayItem(-1, "");
}