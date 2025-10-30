// Fan control header 
#ifndef FAN_CONTROL_H
#define FAN_CONTROL_H

#include "config.h"

void setup_fan_control() {
  pinMode(PIN_RELAY_FAN, OUTPUT);
  digitalWrite(PIN_RELAY_FAN, LOW); // Start OFF
}

// Sets the fan state (true = ON, false = OFF)
// Note: Relays are often Active-LOW (LOW turns them ON).
// This code assumes Active-HIGH. Invert (HIGH/LOW) if your relay is Active-LOW.
void set_fan_state(bool turn_on) {
  digitalWrite(PIN_RELAY_FAN, turn_on ? HIGH : LOW);
}

#endif