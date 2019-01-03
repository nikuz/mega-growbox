#define PRODUCTION 1    // production
//#define PRODUCTION 0    // development

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
#define DHTPin  46
#define HUMIDITY_LEVEL_SENSOR 22
#define WATERING_LEVEL_SENSOR 24

#define SOIL_SENSOR_1 1 // A0
#define SOIL_SENSOR_2 2 // A1
#define SOIL_SENSOR_3 3 // A2
#define SOIL_SENSOR_4 4 // A3

// relays defined in Relay.cpp

#define DOOR_BUTTON 34

#define LIGHT_KNOB_SERVO 12

#define RAIN_SENSOR_1 33
#define RAIN_SENSOR_2 31
#define RAIN_SENSOR_3 29
#define RAIN_SENSOR_4 27
