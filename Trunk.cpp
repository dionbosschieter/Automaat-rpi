//
// Created by Dion Bosschieter on 23-04-15.
//

Trunk::Trunk(int number)
{
    this->number = number;
}

void Trunk::setAvailable(int available)
{
    this->available = available;
}

void Trunk::setBillType(int billType)
{
    this->billType = billType;
}

void Trunk::resetAmountOfTurns()
{
    this->amountOfTurns = 0;
}

void Trunk::incrementAmountOfTurns()
{
    this->amountOfTurns++;
}

void Trunk::decrementAvailable()
{
    this->available--;
}

void Trunk::decrementAmountOfTurns()
{
    this->amountOfTurns--;
}

int Trunk::getNumber()
{
    return this->number;
}

int Trunk::getBillType()
{
    return this->billType;
}

int Trunk::getAvailable()
{
    return this->available;
}

int Trunk::getAmountOfTurns()
{
    return this->amountOfTurns;
}
