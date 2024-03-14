#pragma once

#include <bakanetpch.h>
#include <bakanet/tools/string_tools.h>

#define HTTP_RES_200 "200 OK"

#define HTTP_RES_303 "303 See Other"

#define HTTP_RES_400 "400 Bad Request"
#define HTTP_RES_401 "401 Unauthorized"
#define HTTP_RES_402 "402 Payment Required"
#define HTTP_RES_403 "403 Forbidden"
#define HTTP_RES_404 "404 Not Found"
#define HTTP_RES_405 "405 Method Not Allowed"
#define HTTP_RES_406 "406 Not Acceptable"
#define HTTP_RES_408 "408 Request Timeout"

namespace Bk::Net {
    using HttpParams = std::unordered_map<std::string, std::string>;

    class HttpRequest 
    {
        public:
            HttpRequest(std::string method, 
            std::string url,
            std::string version,
            HttpParams params = HttpParams(0),
            std::string body = "");

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
            HttpParams params = HttpParams(0),
            std::string body = "");

            HttpReponse(std::string data);

            std::string to_string();

            std::string status;
            std::string version;
            HttpParams params;
            std::string body;
    };
}