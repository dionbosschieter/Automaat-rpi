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
        int getTicketWinAmount();
        int fetchStatus();
        void pushStatus(int status);

    private:
        HTTP *client;
        const char *apikey;
        std::string apiResponse;

        std::map<std::string, std::string> getDefaultQueryArray();
        int getIntegerFromApiResponse();
        void setApiData(std::map<std::string, std::string> queryMap);
};


#endif //_AUTOMAAT_AUTOMAATAPI_H
