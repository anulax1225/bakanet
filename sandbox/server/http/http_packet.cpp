#include "http_packet.h"
#include <iomanip>

HttpRequest::HttpRequest(std::string method,
std::string url,
std::string version,
HttpParams params,
std::string body) 
: method(method), url(url), version(version), params(params), body(body) {}

HttpRequest::HttpRequest(std::string data)
{
    log(data)
    auto lines = string_split(data, "\n");
    auto first_line = std::string(lines->at(0));
    auto req_data = string_split(first_line, " ");
    method = req_data->at(0);
    url = req_data->at(1);
    version = req_data->at(2);
    body = std::string(lines->at(lines->size() - 1));
    lines->erase(lines->begin());
    lines->erase(lines->end());
    int i = 0;
    for (auto line : *lines)
    {
       log(i << "|" << line) 
       i++;
    }
    log(method << url << version)
    log("BODY|" << body)
    for (auto line : *lines)
    {
        auto param = string_split(line, ":", 1);
        if (param->size() >= 2) 
        {
            string_trim(param->at(1));
            params.insert({param->at(0), param->at(1)});
        }
    }

    for (auto pair : params)
    {
        log(pair.second)
    }
}

std::string HttpRequest::to_string()
{
    std::string request = "";
    request += method + " " + url + " " + version;
    std::string param_order[] = 
    {
        "Host",
        "User-Agent",
        "Accept",
        "Accept-Language",
        "Accept-Encoding",
        "Connection",
        "Upgrade-Insecure-Request",
        "Sec-Fetch-Dest",
        "Sec-Fetch-Mode",
        "Sec-Fetch-Site"
    };
    if (params.size()) for ( const auto& param : param_order) if (params[param].length()) request += param + ": " + params[param] + "\r\n";
    request += "\r\n";
    if (body.length()) request += body;
    return request;
}

HttpReponse::HttpReponse(std::string status,
std::string version,
HttpParams params,
std::string body)
: status(status), version(version), params(params), body(body) {}

HttpReponse::HttpReponse(std::string data)
{
    status = "";
    version = "";
    body = "";
}

std::string HttpReponse::to_string()
{
    std::string reponse = "";
    reponse = version +  " " + status + " \r\n";
    if (params.size()) for ( const auto& pair : params) reponse += pair.first + ": " + pair.second + " \r\n";
    reponse += "\r\n";
    if (body.length()) reponse += body;
    return reponse;
}