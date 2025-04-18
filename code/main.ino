/**
 * Arduino Sensor System
 * Main program integrating PDM microphone and APDS9960 proximity sensor
 */

#include "config.h"
#include "pdm_sensor.h"
#include "proximity_sensor.h"

// Global configuration instance
PinConfig pins;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  // Initialize pins
  pinMode(pins.pdmLedPin, OUTPUT);
  pinMode(pins.proxLedPin, OUTPUT);
  analogWrite(pins.pdmLedPin, 255);  // Microphone LED starts on
  analogWrite(pins.proxLedPin, 0);   // Proximity LED starts off
  
  // Initialize sensors
  setupPDM();
  setupProximity();
  
  Serial.println("Calibration complete");
}

void loop() {
  // Process sensor data
  processPDM();
  processProximity();
}