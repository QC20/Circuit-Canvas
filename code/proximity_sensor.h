/**
 * Proximity sensor declarations
 */

 #ifndef PROXIMITY_SENSOR_H
 #define PROXIMITY_SENSOR_H
 
 // Proximity Sensor Configuration
 struct ProximityConfig {
   int value = 0;           // Raw proximity value (0-255)
   int threshold = 50;      // Minimum proximity to trigger LED
   int maxValue = 200;      // Expected max proximity value
 };
 
 // Function declarations
 void setupProximity();
 void processProximity();
 
 #endif // PROXIMITY_SENSOR_H