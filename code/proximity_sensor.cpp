/**
 * Proximity sensor implementation
 */

 #include <Arduino.h>
 #include <Arduino_APDS9960.h>
 #include "config.h"
 #include "proximity_sensor.h"
 
 // Global instance of proximity configuration
 ProximityConfig prox;
 
 // External reference to pins
 extern PinConfig pins;
 
 void setupProximity() {
   if (!APDS.begin()) {
     Serial.println("Failed to initialize APDS-9960!");
     while (1);  // Halt if initialization fails
   }
 }
 
 void processProximity() {
   if (!APDS.proximityAvailable()) {
     return;  // Exit if no new data
   }
   
   // Read proximity value
   prox.value = APDS.readProximity();  // Range: 0 (far) to 255 (close)
   
   // Map proximity to LED brightness
   int proxBrightness = 0;  // Default (OFF when no object)
   if (prox.value > prox.threshold) {
     // Scale brightness from threshold to maxValue
     float normalized = (float)(prox.value - prox.threshold) / (prox.maxValue - prox.threshold);
     normalized = constrain(normalized, 0.0, 1.0);
     proxBrightness = (int)(255.0 * normalized);
   }
   
   // Update LED
   analogWrite(pins.proxLedPin, proxBrightness);
   
   // Log data
   Serial.print("Proximity: ");
   Serial.print(prox.value);
   Serial.print(" | Prox LED: ");
   Serial.println(proxBrightness);
 }