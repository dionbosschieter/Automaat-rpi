//
// Created by Dion Bosschieter on 17-03-15.
//

#include "KeyPad.h"

char KeyPad::pad[3][4] = {{'1','4','7','*'},{'2','5','8','0'},{'3','6','9','#'}};

KeyPad::KeyPad(int row1, int row2, int row3, int col1, int col2, int col3, int col4)
{
    rows[0] = row1;
    rows[1] = row2;
    rows[2] = row3;

    cols[0] = col1;
    cols[1] = col2;
    cols[2] = col3;
    cols[3] = col4;

    // setup rows
    for(int pin : rows) {
        pinMode(pin, OUTPUT);
    }

    // ...and columns
    for(int pin : cols) {
        pullUpDnControl(pin, PUD_DOWN);
        pinMode(pin, INPUT);
    }
}

KeyPad::~KeyPad()
{
    for(int i=0;i<3;i++) {
        digitalWrite(rows[i], LOW);
    }
}

char KeyPad::getKey()
{
    for(int i=0 ;i < 100;i++) {
        if(i == 3) i = 0;
        digitalWrite (rows[i], HIGH);

        for(int i2 = 0; i2<4;i2++) {
            if(digitalRead(cols[i2]) == 1) {
                for(;;) {
                    // return on keyUp
                    if(digitalRead(cols[i2]) == 0) return pad[i][i2];
                    delay(20);
                }
            }
        }

        delay(20);
        digitalWrite (rows[i], LOW);
    }
}
