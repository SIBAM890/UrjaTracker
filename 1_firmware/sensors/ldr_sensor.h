// LDR sensor header 
#ifndef LDR_SENSOR_H
#define LDR_SENSOR_H

#include "config.h"

// Returns: an integer from 0 (dark) to 1023 (bright)
int read_ldr_level() {
  return analogRead(PIN_SENSOR_LDR);
}

#endif