#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include "../config.h" // <-- CORRECTED: Added "../" back

void setup_light_control() {
  pinMode(PIN_RELAY_LIGHT, OUTPUT);
  digitalWrite(PIN_RELAY_LIGHT, LOW); 
}

void set_light_state(bool turn_on) {
  digitalWrite(PIN_RELAY_LIGHT, turn_on ? HIGH : LOW);
}

#endif