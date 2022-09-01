#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include "gps.h"

static const int RXPin = 4, TXPin = 3;
SoftwareSerial gpsSerial(TXPin, RXPin);
TinyGPSPlus lib_gps; 

void GPS::initialize() {
    gpsSerial.begin(9600);
}

Coordinate GPS::GetCurrentCoordinate() {
    lib_gps.encode(gpsSerial.read());
    Coordinate coor;
    while (gpsSerial.available() > 0) {
        lib_gps.encode(gpsSerial.read());
        if (lib_gps.location.isUpdated()) {
            coor.latitude = lib_gps.location.lat();
            coor.longitude = lib_gps.location.lng();
            Serial.print(F(" LAT=")); Serial.print(lib_gps.location.lat());
            Serial.print(F("\tLON=")); Serial.println(lib_gps.location.lng());
            break;
        }
    }
    return coor;
}
