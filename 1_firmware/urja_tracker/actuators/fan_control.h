#ifndef FAN_CONTROL_H
#define FAN_CONTROL_H

#include "../config.h" // <-- CORRECTED: Added "../" back

void setup_fan_control() {
  pinMode(PIN_RELAY_FAN, OUTPUT);
  digitalWrite(PIN_RELAY_FAN, LOW); 
}

void set_fan_state(bool turn_on) {
  digitalWrite(PIN_RELAY_FAN, turn_on ? HIGH : LOW);
}

#endif