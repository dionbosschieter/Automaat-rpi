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
    stringMap queryMap = getDefaultQueryArray();
    queryMap["ticketnr"] = ticketnr;
    queryMap["webcode"] = webcode;

    std::string query = client->buildQueryFromMap(queryMap);
    client->setPostData(query);
    apiResponse = client->getResponse();
}

stringMap AutomaatApi::getDefaultQueryArray()
{
    stringMap queryArray;
    queryArray["apikey"] = apikey;

    return queryArray;
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

int AutomaatApi::getIntegerFromApiResponse()
{
    std::size_t pos = apiResponse.find(':');
    std::string amount = apiResponse.substr(pos+1);

    return std::stoi(amount);
}

int AutomaatApi::getTicketWinAmount()
{
    return getIntegerFromApiResponse();
}

int AutomaatApi::fetchStatus()
{
    stringMap queryMap = getDefaultQueryArray();
    std::string query = client->buildQueryFromMap(queryMap);
    client->setPostData(query);
    apiResponse = client->getResponse();

    return getIntegerFromApiResponse();
}

void AutomaatApi::pushStatus(std::string status)
{
    stringMap queryMap = getDefaultQueryArray();
    queryMap["status"] = status;

    std::string query = client->buildQueryFromMap(queryMap);
    client->setPostData(query);
    apiResponse = client->getResponse();
}

