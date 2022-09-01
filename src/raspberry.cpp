#include <iostream>
#include <string>
#include "raspberry.h"
#include <Arduino.h>


using namespace std;

Path Raspberry::CollectPath() {
    while (true) {
        Serial.println("RASPBERRY ASK AMOUNT");
        for (int i=0; i < 20; i+=1) { 
            if (Serial.available() > 0) {
                String data="AMOUNT 9999999999";
                for (int i=0; i < 20; i+=1) { 
                    if (data.substring(0, 7) == "AMOUNT ") {
                        String str = data.substring(9, 11);
                        int amount = str.toInt();
                        Path pa;
                        for (int i=0; i < amount; i+=1) {
                            pa.checkpoints[i].longitude = CollectLng(i + 1);
                            pa.checkpoints[i].latitude = CollectLat(i + 1);
                        }
                        return pa;
                    }
                    delay(10);
                }
            }
            delay(10);
        }
    }
}


float Raspberry::CollectLat(int index) {
    char cl[11];
    sprintf(cl, "RASPBERRY ASK POINT %d LAT", index);
    while (true) { 
        Serial.println(cl);
        if (Serial.available() > 0) {
            String data="POINT LNG 9999999999";
            for (int i=0; i < 20; i+=1) { 
                if (data.substring(0, 7) == "POINT LAT ") {
                    String sla = data.substring(9, 11);
                    float fla = sla.toFloat();
                    return fla;             
                }
                delay(10);
            }
        } 
        delay(10);
    }
}

float Raspberry::CollectLng(int index) {
    char cl[11];
    sprintf(cl, "RASPBERRY ASK POINT %d LNG", index);
    while (true) { 
        Serial.println(cl);
        if (Serial.available() > 0) {
            String data="POINT LNG 9999999999";
            for (int i=0; i < 20; i+=1) { 
                if (data.substring(0, 7) == "POINT LAT ") {
                    String sln = data.substring(9, 11);
                    float fln = sln.toFloat();
                    return fln;             
                }
                delay(10);
            }
        }
        delay(10);
    }
}