#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>

// Custom classes
#include "AutomaatApi.h"
#include "Screen.h"
#include "KeyPad.h"
#include "AutomaatApi.h"
#include "Bak.h"

const std::string IDLE = "1";
const std::string BUSY = "2";
const int CLOSETRUNKS = 3;
const char *APIKEY = "/* api key here */";

void backgroundApiCheck(std::mutex *userLock, Bak *bak)
{
    AutomaatApi* api = new AutomaatApi(APIKEY);
    for(;;)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        //pol for status
        if(api->fetchStatus() == CLOSETRUNKS) {
            userLock->lock();
            bak->closeTrunks();
            api->pushStatus(IDLE);
            userLock->unlock();
        }
    }
    delete api;
}

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
    AutomaatApi* api = new AutomaatApi(APIKEY);
    KeyPad* keypad = new KeyPad(17, 27, 22, 10, 9, 11, 5);
    Bak* bak = new Bak(api);
    std::mutex userLock;
    std::thread backgroundApiChecker(backgroundApiCheck, &userLock, bak);

    char ticketnr[16];
    char webcode[16];

    for(;;)
    {
        api->pushStatus(IDLE);
        getInput("Enter ticket nr:", ticketnr, screen, keypad);
        api->pushStatus(BUSY);
        userLock.lock();
        getInput("Enter webcode:", webcode, screen, keypad);

        api->checkTicket(ticketnr, webcode);
        if(api->errorHasOccured()) {
            showError(api->getErrorMessage(), screen, keypad);
            userLock.unlock();
            continue;
        }

        screen->clearScreen();
        int amount = api->getTicketWinAmount();
        char msg[16];
        sprintf(msg, "Giving %i EUR", amount);
        screen->echo(msg, 0);
        screen->echo("Please wait...", 1);

        bak->fetchBillAvailable();
        bak->giveMoney(amount);
        bak->pushBillAvailable();

        userLock.unlock();
    }

    // cleanup
    delete screen;
    delete keypad;
    delete api;
    delete bak;

    return 0;
}
