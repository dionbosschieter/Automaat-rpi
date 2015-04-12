//
// Created by Dion Bosschieter on 12-04-15.
//

#ifndef _AUTOMAAT_BAK_H
#define _AUTOMAAT_BAK_H

#include "Screen.h"
#include "StepperMotor.h"

class Bak {

    public:
        Bak();
        ~Bak();
        void giveMoney(int amount);

    private:
        const int bakAmount[4] = {50, 20, 10, 5};
        int amountPerBak[4] = {0, 0, 0, 0};
        StepperMotor *m;
        Relay *r;

        void calculateAmountOfTurns(int amount);
        void performMoneyDropping();
        void resetAmountPerBak();

}

#endif //_AUTOMAAT_BAK_H_
