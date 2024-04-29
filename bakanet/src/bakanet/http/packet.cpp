#include "packet.h"
namespace Bk::Net {
    HttpRequest::HttpRequest(std::string method,
    std::string url,
    std::string version,
    HttpParams params,
    std::string body) 
    : method(method), url(url), version(version), params(params), body(body) {}

    HttpRequest::HttpRequest(std::string data)
    {
        auto lines = Tools::string_split(data, "\n");
        auto req_data = Tools::string_split(lines->at(0), " ");
        if(req_data->size() > 0) method = req_data->at(0);
        if(req_data->size() > 1) url = req_data->at(1);
        if(req_data->size() > 2) version = req_data->at(2);
        lines->erase(lines->begin());

        for (auto line = lines->begin(); line != lines->end(); line++)
        {
            if (*line != "\r")
            {
                auto param = Tools::string_split(*line, ":", 1);
                if (param->size() >= 2) 
                {
                    Tools::string_trim(param->at(1));
                    params.insert({param->at(0), param->at(1)});
                } 
            }
            else 
            {
                for (auto body_line = ++line; body_line != lines->end(); body_line++) 
                    body += *body_line + "\n";
                break;
            }
        }
    }

    std::string HttpRequest::to_string()
    {
        std::string request = "";
        request += method + " " + url + " " + version + "\r\n";
        if (params.size()) for ( const auto& param : params) request += param.first + ": " + param.second + "\r\n";
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
        //To do
        status = "";
        version = "";
        params = HttpParams(0);
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
}