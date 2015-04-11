#include <iostream>

// Custom classes
#include "AutomaatApi.h"
#include "Relay.h"
#include "Screen.h"
#include "StepperMotor.h"
#include "KeyPad.h"
#include "AutomaatApi.h"

using namespace std;

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

void giveMoney(int amount)
{
    
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

    getInput("Enter ticket nr:", ticketnr, s, k);
    getInput("Enter webcode:", webcode, s, k);

    api->checkTicket(ticketnr, webcode);
    if(api->errorHasOccured()) {
        showError(api->getErrorMessage(), s, k);
    } else {
        amountOfMoney = api->getAmount();
        giveMoney(amountOfMoney);
    }

    delete s;
    delete r;
    delete m;
    delete k;
    delete api;

    return 0;
}
