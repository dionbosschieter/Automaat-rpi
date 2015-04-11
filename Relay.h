//
// Created by Dion Bosschieter on 16-03-15.
//

#ifndef _AUTOMAAT_RELAY_H_
#define _AUTOMAAT_RELAY_H_

#include <wiringPi.h>

class Relay {

private:
    int pins[4];

public:
    Relay(int p1, int p2, int p3, int p4);
    ~Relay();
    void turnOn(int i);
    void turnOff(int i);

};


#endif //_AUTOMAAT_RELAY_H_
