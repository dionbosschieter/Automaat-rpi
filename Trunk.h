//
// Created by Dion Bosschieter on 23-04-15.
//

#ifndef _AUTOMAAT_TRUNK_H
#define _AUTOMAAT_TRUNK_H

class Trunk {

public:
    Trunk(int number);
    void setAvailable(int available);
    void setBillType(int billType);
    void resetAmountOfTurns();
    void incrementAmountOfTurns();
    void decrementAvailable();
    void decrementAmountOfTurns();

    int getNumber();
    int getBillType();
    int getAvailable();
    int getAmountOfTurns();

private:
    int number;
    int billType;
    int available;
    int amountOfTurns;

};

#endif //_AUTOMAAT_TRUNK_H_
