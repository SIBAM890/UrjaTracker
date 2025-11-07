#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include "config.h" // <-- CORRECTED: Removed "../"

void setup_ir_sensor() {
  pinMode(PIN_SENSOR_PIR, INPUT);
}

// Returns: true if motion is detected, false otherwise
bool read_ir_presence() {
  return digitalRead(PIN_SENSOR_PIR) == HIGH;
}

#endif