//
// Created by Dion Bosschieter on 12-04-15.
//

#ifndef _AUTOMAAT_BAK_H
#define _AUTOMAAT_BAK_H

#include "Relay.h"
#include "StepperMotor.h"
#include "AutomaatApi.h"

class Bak {

    public:
        Bak(AutomaatApi *api);
        ~Bak();
        void giveMoney(int amount);
        void fetchBillAvailable();
        void pushBillAvailable();

    private:
        const int trunkBilltype[4] = {50, 20, 10, 5};
        int amountPerTrunk[4] = {0, 0, 0, 0};
        StepperMotor *motor;
        Relay *relay;
        AutomaatApi *api;

        void calculateAmountOfTurns(int amount);
        void performMoneyDropping();
        void resetAmountPerBak();

};

#endif //_AUTOMAAT_BAK_H_
