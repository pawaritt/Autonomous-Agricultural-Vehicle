#include <Arduino.h>
#include <math.h>
#include "compass.h"

void Compass :: initialize() {
    if(!mag.begin()) {
        Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
        while(1);
    }
    
    /* Display some basic information on this sensor */
    displaySensorDetails();
}

float Compass :: GetDirectionDegree() {
    sensors_event_t event; 
    mag.getEvent(&event);
    
    /* Display the results (magnetic vector values are in micro-Tesla (uT)) */

    // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
    // Calculate heading when the magnetometer is level, then correct for signs of axis.
    float heading = atan2(event.magnetic.y, event.magnetic.x);
    
    // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
    // Find yours here: http://www.magnetic-declination.com/
    // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
    // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
    float declinationAngle = 0.22;
    heading += declinationAngle;
    
    // Correct for when signs are reversed.
    if(heading < 0) {
        heading += 2*PI;
    }
        
    // Check for wrap due to addition of declination.
    if(heading > 2*PI) {
        heading -= 2*PI;
    }

    float headingDegrees = heading * 180/PI;       
    return headingDegrees;
}

void Compass :: displaySensorDetails() {
    sensor_t sensor;
    mag.getSensor(&sensor);
    Serial.println("------------------------------------");
    Serial.print  ("Sensor:       "); Serial.println(sensor.name);
    Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
    Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
    Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
    Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
    Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
    Serial.println("------------------------------------");
    Serial.println("");
    delay(500);
}


