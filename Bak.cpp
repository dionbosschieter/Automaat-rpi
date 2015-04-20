//
// Created by Dion Bosschieter on 12-04-15.
//

#include "Bak.h"

Bak::Bak(AutomaatApi *api)
{
    this->api = api;
    motor = new StepperMotor(12, 16, 20, 21);
    relay = new Relay(6, 13, 19, 26);
}

Bak::~Bak()
{
   delete motor;
   delete relay;
}

void Bak::fetchBillAvailable()
{

}

void Bak::pushBillAvailable()
{
    
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
            if(amount >= trunkBilltype[i]) {
                amount -= trunkBilltype[i];
                amountPerTrunk[i]++; // register the amount
            }

            if(trunkBilltype[i] > amount)
                break;
        }
    }

}

void Bak::resetAmountPerBak()
{
   for(int i = 0;i<4;i++) {
       amountPerTrunk[i] = 0;
   }
}

void Bak::performMoneyDropping()
{
    for(int i=0; i<4;i++) {
        for(;;) {
            // turn until we are done with this drawer
            if(amountPerTrunk[i] > 0) {
                relay->turnOn(i);
                motor->forward();
                amountPerTrunk[i]--;
            }

            if(amountPerTrunk[i] == 0) {
                relay->turnOff(i);
                break;
            }
        }
    }
}
