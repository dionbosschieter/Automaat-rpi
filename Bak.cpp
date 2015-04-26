//
// Created by Dion Bosschieter on 12-04-15.
//
// This class is doing too much

#include "Bak.h"

Bak::Bak(AutomaatApi *api)
{
    this->api = api;
    motor = new StepperMotor(12, 16, 20, 21);
    relay = new Relay(6, 26, 13, 19);

    //create trunks
    for(int i = 0; i<4;i++) {
        trunks[i] = new Trunk( i + 1 );
        trunks[i]->setBillType(trunkBilltype[i]);
    }
}

Bak::~Bak()
{
   delete motor;
   delete relay;

   for(Trunk *trunk : trunks) {
       delete trunk;
   }
}

/**
 * Fetches the state of each trunk from the api
 */
void Bak::fetchBillAvailable()
{
    for(Trunk *trunk : trunks) {
        int available = api->fetchTrunkStateByNumber(trunk->getNumber());
        trunk->setAvailable(available);
    }
}

/**
 * Pushes the state for each trunk to the api
 */
void Bak::pushBillAvailable()
{
    for(Trunk *trunk : trunks) {
        api->pushTrunkStateByNumber(trunk->getNumber(), trunk->getAvailable());
    }
}

void Bak::giveMoney(int amount)
{
    resetAmountPerBak();
    calculateAmountOfTurns(amount);
    performMoneyDropping();
}

void Bak::resetAmountPerBak()
{
    for(Trunk *trunk : trunks) {
        trunk->resetAmountOfTurns();
    }
}

void Bak::calculateAmountOfTurns(int amount)
{
    this->amount = amount;

    //set amount of turns for each trunk
    for(Trunk *trunk : trunks) {
        setAmountOfTurnsForTrunk(trunk);
    }
}

void Bak::setAmountOfTurnsForTrunk(Trunk *trunk)
{
    while(amount >= trunk->getBillType() && trunk->getAvailable() > 0) {
        amount -= trunk->getBillType();
        trunk->incrementAmountOfTurns(); // register the amount
        trunk->decrementAvailable(); //remove amount from available
    }
}

void Bak::performMoneyDropping()
{
    for(Trunk *trunk : trunks) {
        if(trunk->getAmountOfTurns() == 0) continue;
        turnTrunk(trunk);
    }
}

void Bak::turnTrunk(Trunk *trunk)
{
    relay->turnOn(trunk->getNumber());

    while(trunk->getAmountOfTurns() > 0) {
        // turn until we are done with this drawer
        motor->forward();
        trunk->decrementAmountOfTurns();
    }

    relay->turnOff(trunk->getNumber());
}

void Bak::closeTrunks()
{
    for(Trunk *trunk : trunks) 
        relay->turnOn(trunk->getNumber());

    for(int i=0;i<12;i++) 
        motor->backward();

    for(Trunk *trunk : trunks) 
        relay->turnOff(trunk->getNumber());
}
