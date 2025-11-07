// Arduino main sketch 
#include "config.h"
#include "sensors/ir_sensor.h"
#include "sensors/ldr_sensor.h"
#include "sensors/dht_sensor.h"
#include "sensors/power_sensor.h"
#include "actuators/fan_control.h"
#include "actuators/light_control.h"
#include "utils/serial_comm.h"

// Global state variables
ClassroomState g_state; // The single source of truth [cite: 2]
unsigned long g_last_report_time = 0;

// === SETUP: Runs once on boot ===
void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  // Serial.println("URJA-TRACKER Firmware Booting..."); // <-- CORRECTED: Commented out to prevent JSON errors 

  // Initialize all hardware [cite: 4]
  setup_ir_sensor();
  setup_dht_sensor();
  setup_fan_control();
  setup_light_control();
  // LDR and Power sensors are analog, no setup needed.
  
  // Serial.println("System Initialized. Running..."); // <-- CORRECTED: Commented out to prevent JSON errors [cite: 5]
}

// === LOOP: Runs forever ===
void loop() {
  
  // 1. SENSE: Read all sensors
  g_state.person_present = read_ir_presence();
  g_state.ldr_level = read_ldr_level(); [cite: 6]
  
  DhtReadings dht_data = read_dht_data();
  if (dht_data.read_success) {
    g_state.temperature = dht_data.temperature;
    g_state.humidity = dht_data.humidity;
  } [cite: 7]
  
  // 2. THINK: Apply control logic
  
  // --- Light Logic ---
  if (g_state.person_present && g_state.ldr_level < THRESHOLD_LIGHT_DARK) {
    g_state.light_on = true;
  } else if (!g_state.person_present || g_state.ldr_level > THRESHOLD_LIGHT_BRIGHT) { [cite: 8]
    g_state.light_on = false;
  } [cite: 9]
  
  // --- Fan Logic ---
  if (g_state.person_present && g_state.temperature > THRESHOLD_TEMP_HOT) {
    g_state.fan_on = true;
  } else if (!g_state.person_present) { [cite: 10]
    g_state.fan_on = false;
  } [cite: 11]
  
  // 3. ACT: Control the relays
  set_light_state(g_state.light_on);
  set_fan_state(g_state.fan_on);

  // 4. REPORT: Send data to PC (non-blocking) [cite: 12]
  unsigned long current_time = millis();
  if (current_time - g_last_report_time >= REPORT_INTERVAL) { [cite: 13]
    g_last_report_time = current_time;
    
    // Read power *just* before sending [cite: 14]
    g_state.power_watts = read_power_watts();
    
    // Send the complete packet [cite: 15]
    send_serial_data(g_state);
  }
}
// <-- CORRECTED: The extra '}' bracket from your file [cite: 15] has been removed.