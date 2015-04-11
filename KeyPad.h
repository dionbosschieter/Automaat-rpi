//
// Created by Dion Bosschieter on 17-03-15.
//

#ifndef _AUTOMAAT_KEYPAD_H_
#define _AUTOMAAT_KEYPAD_H_

#include <wiringPi.h>

class KeyPad {

    private:
        int rows[3];
        int cols[4];
        static char pad[3][4];

    public:
        KeyPad(int row1, int row2, int row3, int col1, int col2, int col3, int col4);
        ~KeyPad();
        char getKey();
};


#endif //_AUTOMAAT_KEYPAD_H_
