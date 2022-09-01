#include <math.h>
#include "controller.h"
#include "raspberry.h"
#define RADIO_TERRESTRE 6372797.56085
#define GRADOS_RADIANES PI / 180
using namespace std;


void Controller :: start() {
    gps.initialize();
    compass.initialize();
    pinMode(motor1pin1, OUTPUT);
    pinMode(motor1pin2, OUTPUT);
    pinMode(motor2pin1, OUTPUT);
    pinMode(motor2pin2, OUTPUT);
    pinMode(motor1speed, OUTPUT);
    pinMode(motor2speed, OUTPUT);
    analogWrite(motor1speed, 255); 
    analogWrite(motor2speed, 255);
}


void Controller :: FollowPath(Path & follow_path) {
    int length = sizeof(follow_path.checkpoints);
    for (int i = 0; i < length; i++) {
        GetToCoordinate(follow_path.checkpoints[i]);
    }
}

void Controller :: GetToCoordinate(Coordinate & tar_cor){
    float distance, bearing;
    Coordinate cur_cor;
    while (distance > 1) {
        cur_cor = gps.GetCurrentCoordinate();
        distance = CalcDistance(cur_cor, tar_cor);
        bearing = CalcBearing(cur_cor, tar_cor); // in Meters
        AdjustCarDirection(bearing);
        Move();
    }
}

void Controller :: Move(){
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
}

void Controller :: AdjustCarDirection(float target_bearing) {  
    float current_bearing, bearing_dif;
    current_bearing = compass.GetDirectionDegree();
    bearing_dif = current_bearing - target_bearing;
    if (abs(bearing_dif) > 90) {
        delay(500);
        Rotate(target_bearing);
        return;
    }
    if (bearing_dif < 0) {
        analogWrite(motor1speed, abs(bearing_dif) * (255/90)); // range 0 - 255
        analogWrite(motor2speed, 255); // range 0 - 255
    } 
    if (bearing_dif > 0) {
        analogWrite(motor1speed, 255); // range 0 - 255
        analogWrite(motor2speed, abs(bearing_dif) * (255/90)); // range 0 - 255
    }
}

void Controller :: Rotate(float bearing) {
    float current_bearing, bearing_dif, target_bearing;
    while ((bearing_dif) > 2.5) { 
        current_bearing = compass.GetDirectionDegree();
        bearing_dif = current_bearing - target_bearing;
        analogWrite(motor1speed, abs(bearing_dif) * (255/360)); // range 0 - 255
        analogWrite(motor2speed, abs(bearing_dif) * (255/360)); // range 0 - 255
        if (bearing_dif < 0) {
            digitalWrite(motor1pin1, LOW);
            digitalWrite(motor1pin2, HIGH);
            digitalWrite(motor2pin1, HIGH);
            digitalWrite(motor2pin2, LOW);
        } 
        if (bearing_dif > 0) {
            digitalWrite(motor1pin1, HIGH);
            digitalWrite(motor1pin2, LOW);
            digitalWrite(motor2pin1, LOW);
            digitalWrite(motor2pin2, HIGH);
        }
    }
}

float Controller :: CalcDistance(Coordinate & initial_coordinate, Coordinate & target_coordinate){
    double haversine, temp, distancia_puntos;
    float latitud1, longitud1, latitud2, longitud2;

    latitud1  = initial_coordinate.latitude * GRADOS_RADIANES;
    longitud1 = initial_coordinate.longitude * GRADOS_RADIANES;
    latitud2  = target_coordinate.latitude * GRADOS_RADIANES;
    longitud2 = target_coordinate.longitude * GRADOS_RADIANES;

    haversine = (pow(sin((1.0 / 2) * (latitud2 - latitud1)), 2)) + ((cos(latitud1)) * (cos(latitud2)) * (pow(sin((1.0 / 2) * (longitud2 - longitud1)), 2)));
    temp = 2 * asin(min(1.0, sqrt(haversine)));
    distancia_puntos = RADIO_TERRESTRE * temp;

    return distancia_puntos;
}
        
float Controller :: CalcBearing(Coordinate & initial_coordinate, Coordinate & target_coordinate) {
    float X, y, b_deg, b_rad;
    X = cos(target_coordinate.latitude) * sin(abs(target_coordinate.longitude - initial_coordinate.longitude));
    y = cos(initial_coordinate.latitude) * sin(target_coordinate.latitude) - sin(initial_coordinate.longitude) * cos(target_coordinate.latitude) * cos(abs(target_coordinate.longitude - initial_coordinate.longitude));
    b_rad = atan2(X, y); // bearing in radian
    b_deg = b_rad * (180.0/PI); // convert to degree
    return b_deg;
}

