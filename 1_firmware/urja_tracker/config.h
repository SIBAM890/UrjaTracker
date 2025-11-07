// Configuration header file 
#ifndef CONFIG_H
#define CONFIG_H

// === SERIAL COMMUNICATION ===
#define SERIAL_BAUD_RATE 9600
#define JSON_DOC_SIZE 256     // ArduinoJson buffer size (bytes)
#define REPORT_INTERVAL 2000  // Send data every 2000ms (2 seconds)

// === SENSOR PINS ===
#define PIN_SENSOR_PIR 2       // Digital pin for PIR Motion Sensor
#define PIN_SENSOR_LDR A0      // Analog pin for LDR Light Sensor
#define PIN_SENSOR_DHT 3       // Digital pin for DHT11 Temp/Humidity
#define PIN_SENSOR_POWER A1    // Analog pin for ACS712 Current Sensor

// === ACTUATOR PINS ===
#define PIN_RELAY_LIGHT 4    // Digital pin for Light Relay
#define PIN_RELAY_FAN 5      // Digital pin for Fan Relay

// === SENSOR MODELS & CALIBRATION ===
#define DHT_TYPE DHT11       // Specify DHT sensor type

// ACS712 (Current Sensor) Calibration:
// This is for the 5A model. Adjust as needed.
#define ACS_MV_PER_AMP 185   
#define ACS_ZERO_POINT 512   // Calibrated ADC value at 0 Amps

// LDR (Light Sensor) Logic Thresholds (0-1023)
#define THRESHOLD_LIGHT_DARK 300 // LDR value below which room is "dark"
#define THRESHOLD_LIGHT_BRIGHT 700 // LDR value above which room is "bright"

// DHT (Temperature) Logic Thresholds (Celsius)
#define THRESHOLD_TEMP_HOT 28.0 // Temp above which fan turns ON

#endif