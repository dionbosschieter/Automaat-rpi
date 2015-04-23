//
// Created by Dion Bosschieter on 16-03-15.
//

#include "Relay.h"

Relay::Relay(int p1, int p2, int p3, int p4)
{
    this->pins[0] = p1;
    this->pins[1] = p2;
    this->pins[2] = p3;
    this->pins[3] = p4;

    // Setup pins
    for(int i = 0; i < 4; i++) {
        pinMode (pins[i], OUTPUT);
        digitalWrite (pins[i], LOW);
    }
}

Relay::~Relay()
{
    // Disable pins
    for(int i = 0; i < 4; i++) {
        digitalWrite (pins[i], LOW);
    }
}

void Relay::turnOn(int i)
{
    digitalWrite (pins[i - 1], HIGH);
}

void Relay::turnOff(int i)
{
    digitalWrite (pins[i - 1], LOW);
}
