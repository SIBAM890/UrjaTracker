#ifndef POWER_SENSOR_H
#define POWER_SENSOR_H

#include "config.h" // <-- CORRECTED: Removed "../"

// Returns: Estimated power in Watts (W)
double read_power_watts() {
  int sensor_value = analogRead(PIN_SENSOR_POWER);
  
  // Convert analog reading (0-1023) to voltage (0-5000mV)
  double voltage_mv = (sensor_value / 1023.0) * 5000.0;
  
  // Convert voltage to Amps (Absolute value)
  double current_amps = abs((voltage_mv - 2500.0) / ACS_MV_PER_AMP);
  
  // P = V * I. Assume V = 230V
  const double MAINS_VOLTAGE = 230.0; 
  return MAINS_VOLTAGE * current_amps;
}

#endif