//
// Created by Dion Bosschieter on 16-03-15.
//

#ifndef _AUTOMAAT_SCREEN_H_
#define _AUTOMAAT_SCREEN_H_

#include <wiringPi.h>
#include <lcd.h>

class Screen {

public:
    Screen(int rs, int e, int d4, int d5, int d6, int d7);
    void echo(char const *msg, int row);
    void clearScreen();

private:
    int lcd;
};


#endif //_AUTOMAAT_SCREEN_H_
