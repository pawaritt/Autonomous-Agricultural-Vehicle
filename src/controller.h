#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "gps.h"
#include "compass.h"
#include "raspberry.h"

class Controller {
    public:
        void start();
        void FollowPath(Path & follow_path);
        void GetToCoordinate(Coordinate & tar_cor);
        void Rotate(float bearing);
        void Move();
    private:
        GPS gps;
        Compass compass;
        int motor1pin1 = 9;
        int motor1pin2 = 10;
        int motor2pin1 = 11;
        int motor2pin2 = 12;
        int motor1speed = 8;
        int motor2speed = 13;
        void AdjustCarDirection(float bearing);
        float CalcDistance(Coordinate & initial_coordinate, Coordinate & target_coordinate);
        float CalcBearing(Coordinate & initial_coordinate, Coordinate & target_coordinate);
};
#endif