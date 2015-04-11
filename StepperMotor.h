//
// Created by Dion Bosschieter on 14-03-15.
//

#ifndef _AUTOMAAT_STEPPERMOTOR_H_
#define _AUTOMAAT_STEPPERMOTOR_H_

#include <wiringPi.h>

class StepperMotor {

public:
    StepperMotor(int pin1, int pin2, int pin3, int pin4);
    ~StepperMotor();
    void drive(bool forward);
    void forward();
    void backward();

private:
    int pin1, pin2, pin3, pin4;
    static int timeout;
    static int totalSteps;

    void drive(int p1, int p2, int p3, int p4);
    void turnOff();
};


#endif //_AUTOMAAT_STEPPERMOTOR_H_
