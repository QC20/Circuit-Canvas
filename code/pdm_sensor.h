/**
 * PDM Microphone sensor declarations
 */

 #ifndef PDM_SENSOR_H
 #define PDM_SENSOR_H
 
 // PDM Microphone Configuration
 struct PDMConfig {
   volatile short sampleBuffer[256];
   volatile int samplesRead = 0;
   volatile bool samplesReady = false;
   float smoothedRms = 0;
   float alpha = 0.3;       // Smoothing factor
   float threshold = 15.0;  // Adjust based on your environment
   float maxRms = 50.0;     // Adjust based on loud sounds
 };
 
 // Function declarations
 void setupPDM();
 void processPDM();
 void onPDMdata();
 
 #endif // PDM_SENSOR_H