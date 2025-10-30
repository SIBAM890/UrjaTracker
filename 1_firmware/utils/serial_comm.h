// Serial communication helper 
#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include "config.h"
#include <ArduinoJson.h> // ArduinoJson Library

// This struct holds the complete state of the classroom
struct ClassroomState {
  bool person_present;
  int ldr_level;
  float temperature;
  float humidity;
  double power_watts;
  bool light_on;
  bool fan_on;
};

// Sends the complete state as a single JSON line over Serial
void send_serial_data(ClassroomState &state) {
  StaticJsonDocument<JSON_DOC_SIZE> doc;

  doc["presence"] = state.person_present;
  doc["light_level"] = state.ldr_level;
  doc["temperature_c"] = state.temperature;
  doc["humidity_pct"] = state.humidity;
  doc["power_watts"] = state.power_watts;
  doc["light_state"] = state.light_on ? "ON" : "OFF";
  doc["fan_state"] = state.fan_on ? "ON" : "OFF";

  // Print the JSON to the Serial port
  serializeJson(doc, Serial);
  Serial.println(); // Send a newline to mark the end of the message
}

#endif