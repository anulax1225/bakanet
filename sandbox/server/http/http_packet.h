#pragma once

#include <commun.h>
#include "http_tools.h"

using HttpParams = std::unordered_map<std::string, std::string>;

class HttpRequest 
{
    public:
        HttpRequest(std::string method,
        std::string url,
        std::string version,
        HttpParams params,
        std::string body);

        HttpRequest(std::string data);

        std::string to_string();

        std::string method;
        std::string url;
        std::string version;
        HttpParams params;
        std::string body;
};

class HttpReponse
{
    public:
        HttpReponse(std::string status,
        std::string version,
        HttpParams params,
        std::string body);

        HttpReponse(std::string data);

        std::string to_string();

        std::string status;
        std::string version;
        HttpParams params;
        std::string body;
};