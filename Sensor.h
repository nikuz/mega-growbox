#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>

class Sensor {
public:
    Sensor();

    ~Sensor();

    static void initiate();

    static void readDHT();

    static float temperatureGet();

    static float humidityGet();

    static bool humidityHasWater();

    static unsigned int getSoilMoisture(int sensorId, int min, int max);

    static bool wateringHasWater();
};

#endif /* Sensor_h */