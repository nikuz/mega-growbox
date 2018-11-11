//#define PRODUCTION 1    // production
#define PRODUCTION 0    // development

#define VERSION 1

#if PRODUCTION
#define VERSION_MARKER "P"
#else
#define VERSION_MARKER "D"
#endif

// sensors
#if PRODUCTION
#define DHTTYPE DHT22
#else
#define DHTTYPE DHT11
#endif
#define DHTPin  22
#define HUMIDITY_LEVEL_SENSOR 23
#define WATERING_LEVEL_SENSOR 24

#define SOIL_SENSOR_1 0 // A0
#define SOIL_SENSOR_2 1 // A1
#define SOIL_SENSOR_3 2 // A2
#define SOIL_SENSOR_4 3 // A3

// relays defined in Relay.cpp
