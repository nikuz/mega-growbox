#include <Arduino.h>
#include <DHT.h>

#include "def.h"
#include "Sensor.h"
#include "Tools.h"

static DHT dht(DHTPin, DHTTYPE);

float currentTemperature = 0;
float currentHumidity = 0;

Sensor::Sensor() {}

Sensor::~Sensor() {}

void Sensor::initiate() {
    dht.begin();
    pinMode(HUMIDITY_LEVEL_SENSOR, INPUT);
    pinMode(WATERING_LEVEL_SENSOR, INPUT);
}

void Sensor::readDHT() {
    float newTemperature = dht.readTemperature();
    float newHumidity = dht.readHumidity();
    if (isnan(newTemperature) || isnan(newHumidity)) {
        Serial.println("Failed to read from DHT sensor!");
    } else {
        currentTemperature = newTemperature;
        currentHumidity = newHumidity;
    }
}

// temperature

char *Sensor::temperatureGet() {
    char *result = Tools::intToChar(currentTemperature);
    return result;
}

// humidity

char *Sensor::humidityGet() {
    char *result = Tools::intToChar(currentHumidity);
    return result;
}

char *Sensor::humidityHasWater() {
    int hasWater = digitalRead(HUMIDITY_LEVEL_SENSOR);
    return hasWater ? "1" : "0";
}


// soil

char *Sensor::getSoilMoisture(int sensorId) {
    unsigned int moisture = analogRead(sensorId);
    char *result = Tools::intToChar(moisture);
    return result;
}

// watering

char *Sensor::wateringHasWater() {
    int hasWater = digitalRead(WATERING_LEVEL_SENSOR);
    return hasWater ? "1" : "0";
}