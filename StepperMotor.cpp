//
// Created by Dion Bosschieter on 14-03-15.
//

#include "StepperMotor.h"

int StepperMotor::timeout = 10;
int StepperMotor::totalSteps = 100;//350

StepperMotor::StepperMotor(int pin1, int pin2, int pin3, int pin4)
{
    // Setup pins
    pinMode (pin1, OUTPUT);
    pinMode (pin2, OUTPUT);
    pinMode (pin3, OUTPUT);
    pinMode (pin4, OUTPUT);

    this->pin1 = pin1;
    this->pin2 = pin2;
    this->pin3 = pin3;
    this->pin4 = pin4;
}

StepperMotor::~StepperMotor()
{
    turnOff();
}

void StepperMotor::turnOff()
{
    // turn the pins of
    digitalWrite (pin1, LOW);
    digitalWrite (pin2, LOW);
    digitalWrite (pin3, LOW);
    digitalWrite (pin4, LOW);
}

void StepperMotor::drive(int p1, int p2, int p3, int p4)
{
    for(int i=0;i<totalSteps;i++) {
        digitalWrite (p4, LOW);
        digitalWrite (p1, HIGH);
        delay (timeout);
        digitalWrite (p1, LOW);
        digitalWrite (p2, HIGH);
        delay (timeout);
        digitalWrite (p2, LOW);
        digitalWrite (p3, HIGH);
        delay (timeout);
        digitalWrite (p3, LOW);
        digitalWrite (p4, HIGH);
        delay (timeout);
    }

    turnOff();
}

void StepperMotor::forward()
{
    drive(pin1, pin2, pin3, pin4);
}

void StepperMotor::backward()
{
    drive(pin4, pin3, pin2, pin1);
}
