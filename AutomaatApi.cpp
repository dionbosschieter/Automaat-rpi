//
// Created by Dion Bosschieter on 8-04-15.
//

#include "AutomaatApi.h"

AutomaatApi::AutomaatApi(const char *apikey)
{
    client = new HTTP("/* api url here */");
    this->apikey = apikey;
}

AutomaatApi::~AutomaatApi()
{
    delete client;
}

void AutomaatApi::checkTicket(char *ticketnr, char *webcode)
{
    std::map<std::string, std::string> queryArray = getDefaultQueryArray();
    queryArray["ticketnr"] = ticketnr;
    queryArray["webcode"] = webcode;

    std::string queryString = client->buildQueryFromMap(queryArray);
    client->setPostData(queryString);
    apiResponse = client->getResponse();
}

bool AutomaatApi::errorHasOccured()
{
    if(apiResponse.size() == 0 || apiResponse.at(0) == 'E') {
        return true;
    } 

    return false;
}

std::string AutomaatApi::getErrorMessage()
{
    if(apiResponse.size() == 0)
        return "Empty response";

    std::size_t pos = apiResponse.find(':');
    std::string message = apiResponse.substr(pos+1);

    return message;
}

int AutomaatApi::getAmount()
{
    std::size_t pos = apiResponse.find(':');
    std::string amount = apiResponse.substr(pos+1);

    return std::stoi(amount);
}

std::map<std::string, std::string> AutomaatApi::getDefaultQueryArray()
{
    std::map<std::string, std::string> queryArray;
    queryArray["apikey"] = apikey;

    return queryArray;
}


