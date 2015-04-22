//
// Created by Dion Bosschieter on 12-04-15.
//
// This class actually begs for another class called Trunk

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
    availablePerTrunk[0] = api->fetchTrunkStateByNumber(1);
    availablePerTrunk[1] = api->fetchTrunkStateByNumber(2);
    availablePerTrunk[2] = api->fetchTrunkStateByNumber(3);
    availablePerTrunk[3] = api->fetchTrunkStateByNumber(4);
}

/**
 * Pushes the state for each trunk to the api
 */
void Bak::pushBillAvailable()
{
    api->pushTrunkStateByNumber(1, availablePerTrunk[0]);
    api->pushTrunkStateByNumber(2, availablePerTrunk[1]);
    api->pushTrunkStateByNumber(3, availablePerTrunk[2]);
    api->pushTrunkStateByNumber(4, availablePerTrunk[3]);
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
    while(amount >= trunkBilltype[index] && availablePerTrunk[index] > 0) {

        amount -= trunkBilltype[index];
        amountOfTurnsPerTrunk[index]++; // register the amount
        availablePerTrunk[index]--; //remove amount from available

    }
}

void Bak::resetAmountPerBak()
{
   for(int trunkIndex = 0;trunkIndex<4;trunkIndex++) {
       amountOfTurnsPerTrunk[trunkIndex] = 0;
   }
}

void Bak::performMoneyDropping()
{
    for(int trunkIndex=0; trunkIndex<4;trunkIndex++) {
        if(amountOfTurnsPerTrunk[trunkIndex] == 0) continue;
        turnTrunk(trunkIndex);
    }
}

void Bak::turnTrunk(int trunkIndex)
{
    relay->turnOn(trunkIndex);

    while(amountOfTurnsPerTrunk[trunkIndex] > 0) {
        // turn until we are done with this drawer
        motor->forward();
        amountOfTurnsPerTrunk[trunkIndex]--;
    }

    relay->turnOff(trunkIndex);
}
