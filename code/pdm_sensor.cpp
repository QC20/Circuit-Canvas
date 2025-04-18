/**
 * PDM Microphone sensor implementation
 */

 #include <Arduino.h>
 #include <PDM.h>
 #include "config.h"
 #include "pdm_sensor.h"
 
 // Global instance of PDM configuration
 PDMConfig pdm;
 
 // External reference to pins
 extern PinConfig pins;
 
 void setupPDM() {
   PDM.onReceive(onPDMdata);
   PDM.setBufferSize(256 * sizeof(short));
   if (!PDM.begin(1, 16000)) {
     Serial.println("PDM init failed!");
     while (1);  // Halt if initialization fails
   }
 }
 
 void processPDM() {
   if (!pdm.samplesReady) {
     return;  // Exit if no new data
   }
   
   // Calculate RMS of audio samples
   unsigned long long sumSquares = 0;
   for (int i = 0; i < pdm.samplesRead; i++) {
     sumSquares += (pdm.sampleBuffer[i] * pdm.sampleBuffer[i]);
   }
   float rms = sqrt(sumSquares / (float)pdm.samplesRead);
   
   // Apply smoothing filter
   pdm.smoothedRms = pdm.alpha * rms + (1 - pdm.alpha) * pdm.smoothedRms;
   
   // Map RMS to LED brightness (invert: louder = dimmer)
   int pdmBrightness = 255;  // Default brightness (dim when loud)
   if (pdm.smoothedRms > pdm.threshold) {
     float range = pdm.maxRms - pdm.threshold;
     if (range <= 0) range = 1;  // Prevent division by zero
     float normalized = (pdm.smoothedRms - pdm.threshold) / range;
     pdmBrightness = 255 - (int)(normalized * 255);
     pdmBrightness = constrain(pdmBrightness, 0, 255);
   }
   
   // Update LED
   analogWrite(pins.pdmLedPin, pdmBrightness);
   
   // Log data
   Serial.print("Sound: ");
   Serial.print(pdm.smoothedRms);
   Serial.print(" | Mic LED: ");
   Serial.print(pdmBrightness);
   Serial.print(" | ");
   
   // Reset flag
   pdm.samplesReady = false;
 }
 
 void onPDMdata() {
   int bytesAvailable = PDM.available();
   PDM.read((void*)pdm.sampleBuffer, bytesAvailable);
   pdm.samplesRead = bytesAvailable / sizeof(short);
   pdm.samplesReady = true;
 }