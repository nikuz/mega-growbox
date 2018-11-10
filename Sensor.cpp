#include <Arduino.h>
#include <DHT.h>

#include "def.h"
#include "Sensor.h"

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

float Sensor::temperatureGet() {
    Serial.print("DHT temperature: ");
    Serial.println(currentTemperature);
    return currentTemperature;
}

// humidity

float Sensor::humidityGet() {
    Serial.print("DHT humidity: ");
    Serial.println(currentHumidity);
    return currentHumidity;
}

bool Sensor::humidityHasWater() {
    int hasWater = digitalRead(HUMIDITY_LEVEL_SENSOR);
    Serial.print("Humidity has water: ");
    Serial.println(hasWater ? "True" : "False");
    return hasWater ? true : false;
}


// soil

unsigned int Sensor::getSoilMoisture(int sensorId, int min, int max) {
    int value = analogRead(sensorId);

    if (value) {
        value = map(value, min, max, 0, 100);
        if (value < 0) {
            value = 0;
        } else if (value > 100) {
            value = 100;
        }
    }

//    Serial.println("Soil moisture for: " + hasWater ? "True" : "False");
    return value;
}

// watering

bool Sensor::wateringHasWater() {
    int hasWater = digitalRead(WATERING_LEVEL_SENSOR);
    return hasWater ? true : false;
}