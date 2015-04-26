//
// Created by Dion Bosschieter on 12-04-15.
//

#ifndef _AUTOMAAT_BAK_H
#define _AUTOMAAT_BAK_H

#include "Relay.h"
#include "Trunk.h"
#include "StepperMotor.h"
#include "AutomaatApi.h"

class Bak {

    public:
        Bak(AutomaatApi *api);
        ~Bak();
        void giveMoney(int amount);
        void fetchBillAvailable();
        void pushBillAvailable();
        void closeTrunks();

    private:
        const int trunkBilltype[4] = {50, 20, 10, 5};
        int amountOfTurnsPerTrunk[4] = {0, 0, 0, 0};
        int availablePerTrunk[4] = {0, 0, 0, 0};
        int amount;
        StepperMotor *motor;
        Relay *relay;
        AutomaatApi *api;
        Trunk *trunks[4];

        void calculateAmountOfTurns(int amount);
        void performMoneyDropping();
        void resetAmountPerBak();
        void setAmountOfTurnsForTrunk(Trunk *trunk);
        void turnTrunk(Trunk *trunk);

};

#endif //_AUTOMAAT_BAK_H_
