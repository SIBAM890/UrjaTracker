#ifndef POWER_SENSOR_H
#define POWER_SENSOR_H

#include "../config.h" // <-- CORRECTED: Added "../" back

double read_power_watts() {
  int sensor_value = analogRead(PIN_SENSOR_POWER);
  double voltage_mv = (sensor_value / 1023.0) * 5000.0;
  double current_amps = abs((voltage_mv - 2500.0) / ACS_MV_PER_AMP);
  const double MAINS_VOLTAGE = 230.0; 
  return MAINS_VOLTAGE * current_amps;
}

#endif