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
    std::map<std::string, std::string> queryMap = getDefaultQueryArray();
    queryMap["ticketnr"] = ticketnr;
    queryMap["webcode"] = webcode;

    setApiData(queryMap);
    apiResponse = client->getResponse();
}

std::map<std::string, std::string> AutomaatApi::getDefaultQueryArray()
{
    std::map<std::string, std::string> queryArray;
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
    std::map<std::string, std::string> queryMap = getDefaultQueryArray();
    setApiData(queryMap);
    apiResponse = client->getResponse();

    return getIntegerFromApiResponse();
}

void AutomaatApi::pushStatus(int status)
{
    std::map<std::string, std::string> queryMap = getDefaultQueryArray();
    queryMap["status"] = status;

    setApiData(queryMap);
    apiResponse = client->getResponse();
}

void AutomaatApi::setApiData(std::map<std::string, std::string> queryMap)
{
    std::string queryString = client->buildQueryFromMap(queryMap);
    client->setPostData(queryString);
}

