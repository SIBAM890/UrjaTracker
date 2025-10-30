// Light control header 
#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include "config.h"

void setup_light_control() {
  pinMode(PIN_RELAY_LIGHT, OUTPUT);
  digitalWrite(PIN_RELAY_LIGHT, LOW); // Start OFF
}

// Sets the light state (true = ON, false = OFF)
void set_light_state(bool turn_on) {
  digitalWrite(PIN_RELAY_LIGHT, turn_on ? HIGH : LOW);
}

#endif