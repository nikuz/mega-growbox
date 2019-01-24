#define PRODUCTION 1    // production
//#define PRODUCTION 0    // development
//#define DEBUG 1

#define VERSION_ID "1"

#if PRODUCTION
#define VERSION_MARKER "P"
#else
#define VERSION_MARKER "D"
#endif

#define VERSION VERSION_MARKER VERSION_ID

#ifdef DEBUG
#define DEBUG_PRINT(x)  Serial.print(x)
#define DEBUG_PRINTLN(x)  Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
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

#define SOIL_SENSOR_1 4 // A4
#define SOIL_SENSOR_2 3 // A3
#define SOIL_SENSOR_3 2 // A2
#define SOIL_SENSOR_4 1 // A1

// relays defined in Relay.cpp

#define DOOR_BUTTON 34

#define LIGHT_KNOB_SERVO 12

#define RAIN_SENSOR_1 33
#define RAIN_SENSOR_2 31
#define RAIN_SENSOR_3 29
#define RAIN_SENSOR_4 27
