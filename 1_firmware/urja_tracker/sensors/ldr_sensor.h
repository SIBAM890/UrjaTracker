#ifndef LDR_SENSOR_H
#define LDR_SENSOR_H

#include "../config.h" // <-- CORRECTED: Added "../" back

int read_ldr_level() {
  return analogRead(PIN_SENSOR_LDR);
}

#endif