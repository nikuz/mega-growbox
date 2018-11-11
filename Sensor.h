#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>

class Sensor {
public:
    Sensor();

    ~Sensor();

    static void initiate();

    static void readDHT();

    static char *temperatureGet();

    static char *humidityGet();

    static char *humidityHasWater();

    static char *getSoilMoisture(int sensorId);

    static char *wateringHasWater();
};

#endif /* Sensor_h */