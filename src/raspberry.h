#ifndef RASPBERRY_H
#define RASPBERRY_H
#include "gps.h"

typedef struct path {
    Coordinate *checkpoints;
} Path;

class Raspberry {
    public:
        Path CollectPath();
        void UpdateProgress();
    private:
        float CollectLat(int index);
        float CollectLng(int index);
};
#endif
