//
// Created by Dion Bosschieter on 14-03-15.
//

#ifndef _AUTOMAAT_HTTP_H_
#define _AUTOMAAT_HTTP_H_

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <map>

class HTTP {

    public:
        HTTP();
        ~HTTP();
        std::string getResponse();
        void setPostData(std::string postData);
        void setUrl(char const *url);
        std::string buildQueryFromMap(std::map<std::string, std::string> queryArray);

    private:
        CURL *curl;
        std::string buffer;
        static int writer(char *data, size_t size, size_t nmemb, std::string *writerData);
};

#endif //_AUTOMAAT_HTTP_H_
