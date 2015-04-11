#include <iostream>

// Custom classes
#include "AutomaatApi.h"
#include "Relay.h"
#include "Screen.h"
#include "StepperMotor.h"
#include "KeyPad.h"
#include "AutomaatApi.h"

void getInput(const char *msg, char *buffer, Screen *s, KeyPad *k)
{
    s->clearScreen();
    s->echo(msg, 0);
    s->echo("* back - # done", 1);

    //get a ticket nr
    bool cleared = false;
    for(int i=0;i<16;) {
        char key;
        key = k->getKey();
        if(key == '#') break; // we are done.
        if(key == '*' && i > 0) {
            buffer[--i] = ' ';
        } else {
            buffer[i++] = key;
            if(i < 16) buffer[i] = '\0';
        }

        if(!cleared) {
            cleared = true;
            s->clearScreen();
            s->echo(msg, 0);
        }

        s->echo(buffer,1);
    }
}

void showError(std::string message, Screen *s, KeyPad *k)
{
    s->clearScreen();
    s->echo(message.c_str(), 0);
    s->echo("Press # for Ok", 1);
    k->getKey();
}

// ? class
void giveMoney(int amount, StepperMotor *m, Relay *r)
{
    // calculate the times each bak needs to open
    int bakkenAmount[4] = {50, 20, 10, 5};
    int amountPerBak[4] = {0, 0, 0, 0};

    // function getAmountOfTurns() returns amountPerBak
    for(int i=0;i<4;i++) {
        for(;;) { // function
            if(amount >= bakAmount[i]) {
                amount -= bakAmount[i];
                amountPerBak[i]++; // register the amount 
            }

            if(bakAmount[i] > amount)
                break;
        }
    }

    // now we have the x times that the bak each needs to open
    // perform the opennes of each bak

    // function performMoneyDropping(takes argument of int[4] *amountPerBak)
    for(int i=0; i<4;i++) {
        for(;;) { // turn until we are done with this bak/lade
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

    // now we are done
}

int main()
{
    wiringPiSetupGpio();

    Screen* s = new Screen(14, 15, 25, 24, 23, 18);
    AutomaatApi* api = new AutomaatApi("/*apikey-here*/");
    Relay* r = new Relay(6, 13, 19, 26);
    StepperMotor* m = new StepperMotor(12, 16, 20, 21);
    KeyPad* k = new KeyPad(17, 27, 22, 10, 9, 11, 5);

    char ticketnr[16];
    char webcode[16];
    int amountOfMoney;

    for(;;)
    {
        getInput("Enter ticket nr:", ticketnr, s, k);
        getInput("Enter webcode:", webcode, s, k);

        api->checkTicket(ticketnr, webcode);
        if(api->errorHasOccured()) {
            showError(api->getErrorMessage(), s, k);
        } else {
            amountOfMoney = api->getAmount();
            giveMoney(amountOfMoney, m, r);
        }
    }

    // cleanup
    delete s;
    delete r;
    delete m;
    delete k;
    delete api;

    return 0;
}
