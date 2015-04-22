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

/**
 * Fetches the state of each trunk from the api
 */
void Bak::fetchBillAvailable()
{
    api->fetchTrunkStateByNumber(1);
    api->fetchTrunkStateByNumber(2);
    api->fetchTrunkStateByNumber(3);
    api->fetchTrunkStateByNumber(4);
}

/**
 * Pushes the state for each trunk to the api
 */
void Bak::pushBillAvailable()
{
    api->pushTrunkStateByNumber(1);
    api->pushTrunkStateByNumber(2);
    api->pushTrunkStateByNumber(3);
    api->pushTrunkStateByNumber(4);
}

void Bak::giveMoney(int amount)
{
    resetAmountPerBak();
    calculateAmountOfTurns(amount);
    performMoneyDropping();
}

void Bak::calculateAmountOfTurns(int amount)
{
    this->amount = amount;

    //set smount of turns for each trunk
    for(int trunkIndex=0;trunkIndex<4;trunkIndex++)
        setAmountOfTurnsForTrunk(trunkIndex);
}

void Bak::setAmountOfTurnsForTrunk(int index)
{
    while(trunkBilltype[index] > amount) {
        if(amount >= trunkBilltype[index]) {
            amount -= trunkBilltype[index];
            amountPerTrunk[index]++; // register the amount
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
