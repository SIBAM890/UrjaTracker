#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include "../config.h" // <-- CORRECTED: Added "../" back

void setup_ir_sensor() {
  pinMode(PIN_SENSOR_PIR, INPUT);
}

bool read_ir_presence() {
  return digitalRead(PIN_SENSOR_PIR) == HIGH;
}

#endif