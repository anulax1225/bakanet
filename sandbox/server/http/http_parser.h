#include <unordered_map>

#include <commun.h>

#include "http_tools.h"

enum class HttpMethod
{
    NONE = 0,
    GET = 1,
    POST = 2,
    PUT = 3,
    DELETE = 4,
};

class HttpRequest 
{
    public:
        HttpMethod method;
        std::string url;
        std::unordered_map<std::string, std::string> params;
        std::string body;
};

HttpRequest http_parser(std::string req);
HttpMethod http_resolve_methode(std::string method);