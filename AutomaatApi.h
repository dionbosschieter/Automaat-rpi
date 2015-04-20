//
// Created by Dion Bosschieter on 8-04-15.
//

#ifndef _AUTOMAAT_AUTOMAATAPI_H
#define _AUTOMAAT_AUTOMAATAPI_H

#include "HTTP.h"
#include <iostream>
#include <string>
#include <map>

typedef std::map<std::string, std::string> stringMap;

class AutomaatApi {

    public:
        AutomaatApi(const char *apikey);
        ~AutomaatApi();
        void checkTicket(char *ticketnr, char *webcode);
        bool errorHasOccured();
        std::string getErrorMessage();
        int getTicketWinAmount();
        int fetchStatus();
        void pushStatus(std::string status);

    private:
        HTTP *client;
        const char *apikey;
        std::string apiResponse;

        stringMap getDefaultQueryArray();
        int getIntegerFromApiResponse();
};


#endif //_AUTOMAAT_AUTOMAATAPI_H
