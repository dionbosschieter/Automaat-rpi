//
// Created by Dion Bosschieter on 12-04-15.
//

#include "Bak.h"

Bak::Bak()
{
    m = new StepperMotor(12, 16, 20, 21);
    r = new Relay(6, 13, 19, 26);
}

Bak::~Bak()
{
   delete m;
   delete r;
}

void Bak::giveMoney(int amount)
{
    resetAmountPerBak();
    calculateAmountOfTurns(amount);
    performMoneyDropping();
}

void Bak::calculateAmountOfTurns(int amount)
{
    for(int i=0;i<4;i++) {
        for(;;) { 
            if(amount >= bakAmount[i]) {
                amount -= bakAmount[i];
                amountPerBak[i]++; // register the amount 
            }

            if(bakAmount[i] > amount)
                break;
        }
    }
   
}

void Bak::resetAmountPerBak()
{
   for(int i = 0;i<4;i++) {
       amountPerBak[i] = 0;
   }
}

void Bak::performMoneyDropping()
{
    for(int i=0; i<4;i++) {
        for(;;) { 
            // turn until we are done with this drawer
            if(amountPerBak[i] > 0) {
                r->turnOn(i);
                m->forward();
                amountPerBak[i]--;
            }

            if(amountPerBak[i] == 0) {
                r->turnOff(i);
                break;
            }
        }
    }
}
