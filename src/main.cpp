#include <Arduino.h>
#include "controller.h"
#include "gps.h"
#include "raspberry.h"
// #include "test_path.h"
#define PI 3.14159265358979323846
Controller controller;
Coordinate target {12, 13};
GPS gps;

void setup() {
  Serial.begin(9600);
  controller.start();
  gps.initialize();
}


void loop() {
  // Serial.println(1000);
  Coordinate coor = gps.GetCurrentCoordinate();
  // Serial.print(F(" LAT=")); Serial.print(coor.latitude);
  // Serial.print(F("\tLON=")); Serial.println(coor.longitude);
  delay(100);
  // controller.GetToCoordinate(target);
  // controller.Move();
  
  // Raspberry rasp;
  // Path paths = rasp.CollectPath();
  // controller.FollowPath();

}