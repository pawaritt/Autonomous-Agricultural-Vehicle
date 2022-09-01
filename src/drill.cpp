#include <Arduino.h>
#include "drill.h"
#include <Stepper.h>

const int mag = 90;
const int stepsPerRevolution = 90;
Stepper drillstepper(stepsPerRevolution, 10, 11, 12, 13);

void Driller :: initialize() {
    drillstepper.setSpeed(100);
    home();
}

void Driller :: drill() {
    home();
    drillstepper.step(stepsPerRevolution);
    home();
}

void Driller :: home()  {
    bool magr = digitalRead(mag);
    while (magr == LOW) {
        magr = digitalRead(mag);
        drillstepper.step(stepsPerRevolution);
    }
}