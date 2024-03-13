#include "http_parser.h"

HttpRequest http_parser(std::string req)
{
    std::string url = "", method = "", body = "";
    std::unordered_map<std::string, std::string> params;

    auto lines = string_split(req, "\n");

    auto first_line = string_split(lines->at(0), " ");
    method = string_to_upper(first_line->at(0));
    url = first_line->at(1);
    body = lines->at(lines->size() - 1);

    lines->erase(lines->begin());
    lines->pop_back();

    for (auto line : *lines)
    {
        auto param = string_split(line, ":", 1);
        if (param->size() == 2)
        {
            params.insert({ param->at(0), string_trim(param->at(1))});
        }
    }
    return HttpRequest {
        http_resolve_methode(method),
        url,
        params,
        body
    };
}


HttpMethod http_resolve_methode(std::string method)
{
    if (method.compare("GET")) return HttpMethod::GET;
    else if (method.compare("POST")) return HttpMethod::POST;
    else if (method.compare("PUT")) return HttpMethod::PUT;
    else if (method.compare("DELETE")) return HttpMethod::DELETE;
    else return HttpMethod::NONE;
}