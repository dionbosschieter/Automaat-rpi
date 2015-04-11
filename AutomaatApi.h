//
// Created by Dion Bosschieter on 8-04-15.
//

#ifndef _AUTOMAAT_AUTOMAATAPI_H
#define _AUTOMAAT_AUTOMAATAPI_H

#include "HTTP.h"
#include <iostream>
#include <string>
#include <map>

class AutomaatApi {

    public:
        AutomaatApi(const char *apikey);
        ~AutomaatApi();
        void checkTicket(char *ticketnr, char *webcode);
        bool errorHasOccured();
        std::string getErrorMessage();
        int getAmount();

    private:
        HTTP *client;
        const char *apikey;
        std::map<std::string, std::string> getDefaultQueryArray();
        std::string apiResponse;
};


#endif //_AUTOMAAT_AUTOMAATAPI_H
