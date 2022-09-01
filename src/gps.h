#ifndef GPS_H
#define GPS_H

struct coordinate {
    float latitude;
    float longitude;
}; 

typedef struct coordinate Coordinate;
 
class GPS{
    public:
        void initialize();
        Coordinate GetCurrentCoordinate();
};
#endif