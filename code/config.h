/**
 * Configuration declarations for the sensor system
 */

 #ifndef CONFIG_H
 #define CONFIG_H
 
 // Pin Configuration
 struct PinConfig {
   const int pdmLedPin = 10;   // LED for PDM microphone
   const int proxLedPin = 11;  // LED for proximity sensor
 };
 
 // Make pins available to all modules
 extern PinConfig pins;
 
 #endif // CONFIG_H