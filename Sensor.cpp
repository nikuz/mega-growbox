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

char *Sensor::temperatureGet() {
    static char temperatureStr[2];
    int strLength = 1;
    if (currentTemperature > 10) {
        strLength = 2;
    }
    dtostrf(currentTemperature, strLength, 0, temperatureStr);

    Serial.print("DHT temperature: ");
    Serial.println(temperatureStr);

    return temperatureStr;
}

// humidity

char *Sensor::humidityGet() {
    static char humidityStr[2];
    int strLength = 1;
    if (currentHumidity > 10) {
        strLength = 2;
    }
    dtostrf(currentHumidity, strLength, 0, humidityStr);

    Serial.print("DHT humidity: ");
    Serial.println(humidityStr);

    return humidityStr;
}

char *Sensor::humidityHasWater() {
    int hasWater = digitalRead(HUMIDITY_LEVEL_SENSOR);
    Serial.print("Humidity has water: ");
    Serial.println(hasWater ? "True" : "False");
    return hasWater ? "1" : "0";
}


// soil

char *Sensor::getSoilMoisture(int sensorId) {
    unsigned int moisture = analogRead(sensorId);
    static char moistureStr[4];
    int strLength = 1;
    if (moisture > 10) {
        strLength = 2;
    } else if (moisture > 99) {
        strLength = 3;
    } else if (moisture > 999) {
        strLength = 4;
    }
    dtostrf(moisture, strLength, 0, moistureStr);

    return moistureStr;
}

// watering

char *Sensor::wateringHasWater() {
    int hasWater = digitalRead(WATERING_LEVEL_SENSOR);
    Serial.print("Watering has water: ");
    Serial.println(hasWater ? "True" : "False");
    return hasWater ? "1" : "0";
}