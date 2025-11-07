// DHT sensor header 
#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include "config.h" // <-- CORRECTED: Removed the "../"

#include <DHT.h> // Adafruit DHT Library

DHT dht(PIN_SENSOR_DHT, DHT_TYPE);

struct DhtReadings {
  float temperature = 0.0;
  float humidity = 0.0;
  bool read_success = false;
};

void setup_dht_sensor() {
  dht.begin();
}

DhtReadings read_dht_data() {
  DhtReadings readings;
  readings.humidity = dht.readHumidity();
  readings.temperature = dht.readTemperature(); // Celsius

  if (isnan(readings.humidity) || isnan(readings.temperature)) {
    // Serial.println("Error: Failed to read from DHT sensor!"); // <-- CORRECTED: Commented out to prevent JSON errors
    readings.read_success = false;
  } else {
    readings.read_success = true;
  }
  return readings;
}

#endif