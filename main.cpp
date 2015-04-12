#include <iostream>

// Custom classes
#include "AutomaatApi.h"
#include "Screen.h"
#include "KeyPad.h"
#include "AutomaatApi.h"
#include "Bak.h"

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

int main()
{
    wiringPiSetupGpio();

    Screen* screen = new Screen(14, 15, 25, 24, 23, 18);
    AutomaatApi* api = new AutomaatApi("/*apikey-here*/");
    KeyPad* keypad = new KeyPad(17, 27, 22, 10, 9, 11, 5);
    Bak* bak = new Bak();
    
    char ticketnr[16];
    char webcode[16];

    for(;;)
    {
        getInput("Enter ticket nr:", ticketnr, screen, keypad);
        getInput("Enter webcode:", webcode, screen, keypad);

        api->checkTicket(ticketnr, webcode);
        if(api->errorHasOccured()) {
            showError(api->getErrorMessage(), screen, keypad);
        } else {
            bak->giveMoney(api->getAmount());
        }
    }

    // cleanup
    delete screen;
    delete k;
    delete api;
    delete bak;

    return 0;
}
