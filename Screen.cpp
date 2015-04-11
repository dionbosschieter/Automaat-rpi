//
// Created by Dion Bosschieter on 16-03-15.
//

#include "Screen.h"

Screen::Screen(int rs, int e, int d4, int d5, int d6, int d7)
{
    lcd = lcdInit(2, 16, 4, rs, e, d4, d5, d6, d7, 0, 0, 0, 0);
    delay(20); // give it some time
    clearScreen();
    lcdHome(lcd);
    delay(20);
}

void Screen::clearScreen()
{
    lcdClear(lcd);
    delay(20); // give it some time
}

void Screen::echo(const char * msg, int row)
{
    lcdHome(lcd); // set the cursor to home
    delay(20); // give it some time
    lcdPosition(lcd, 0, row); // set the cursor postition
    delay(20); // give it some time
    lcdPrintf(lcd, msg);
}
