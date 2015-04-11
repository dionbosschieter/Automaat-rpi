//
// Created by Dion Bosschieter on 14-03-15.
//

#include "HTTP.h"

using namespace std;

HTTP::HTTP(char const *url)
{
    CURLcode res;
    // Get a curl handle
    curl = curl_easy_init();

    // Set the url
    curl_easy_setopt(curl, CURLOPT_URL, url);

    res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    if (res != CURLE_OK)
        printf("Failed to set write data\n");

    res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    if (res != CURLE_OK)
        printf("Failed to set writer");
}

HTTP::~HTTP()
{
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

/**
* libcurl write callback function
*/
int HTTP::writer(char *data, size_t size, size_t nmemb, std::string *writerData)
{
    if (writerData == NULL)
        return 0;

    writerData->append(data, size*nmemb);

    return size * nmemb;
}

void HTTP::setPostData(std::string postData)
{
    // build the POST data and set it 
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
}

std::string HTTP::buildQueryFromMap(std::map<std::string, std::string> queryArray)
{
    std::string query;
    int i=0;

    for(const auto& curr : queryArray) {
        query += curr.first + "=" + curr.second;
        if(++i != queryArray.size()) query += "&";
    }

    return query;
}

std::string HTTP::getResponse()
{
    CURLcode res;
    buffer = "";

    if(curl) {
        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    return buffer;
}
