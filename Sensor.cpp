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
    digitalWrite(HUMIDITY_LEVEL_SENSOR, HIGH);
    pinMode(WATERING_LEVEL_SENSOR, INPUT);
    digitalWrite(WATERING_LEVEL_SENSOR, HIGH);
    pinMode(DOOR_BUTTON, INPUT);
    digitalWrite(DOOR_BUTTON, HIGH);
    pinMode(RAIN_SENSOR_1, INPUT);
    digitalWrite(RAIN_SENSOR_1, HIGH);
    pinMode(RAIN_SENSOR_2, INPUT);
    digitalWrite(RAIN_SENSOR_2, HIGH);
    pinMode(RAIN_SENSOR_3, INPUT);
    digitalWrite(RAIN_SENSOR_3, HIGH);
    pinMode(RAIN_SENSOR_4, INPUT);
    digitalWrite(RAIN_SENSOR_4, HIGH);
}

void Sensor::readDHT() {
    float newTemperature = dht.readTemperature();
    float newHumidity = dht.readHumidity();
    if (isnan(newTemperature) || isnan(newHumidity)) {
        DEBUG_PRINTLN("Failed to read from DHT sensor!");
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
    return !hasWater ? "1" : "0"; // inverted
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
    return !hasWater ? "1" : "0"; // inverted
}

// door button

char *Sensor::doorIsOpen() {
    int doorIsOpen = digitalRead(DOOR_BUTTON);
    return !doorIsOpen ? "1" : "0"; // inverted because button has only two pins and pulled up by default
}

// rain

char *Sensor::getRainStatus(int sensorId) {
    unsigned int rain = digitalRead(sensorId);
    return !rain ? "1" : "0"; // inverted
}