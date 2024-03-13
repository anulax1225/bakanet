#include "http_tools.h"

std::string string_to_lower(std::string& str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = std::tolower(str[i]);
    }
    return str;
}

std::string string_to_upper(std::string& str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = std::toupper(str[i]);
    }
    return str;
}

std::unique_ptr<std::vector<std::string>> string_split(std::string& str, std::string delimiter, int cpt)
{
    std::string s(str);
    std::unique_ptr<std::vector<std::string>> splits(new std::vector<std::string>(0));
    size_t pos = 0;
    while (((pos = s.find(delimiter)) != std::string::npos) && cpt-- != 0) 
    {
        splits->push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    if (s.length()) splits->push_back(s);
    return splits;
}

void string_trim(std::string& str, const std::string& whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    const auto strEnd = str.find_last_not_of(whitespace);
    if (strBegin != std::string::npos)
    {
        str.erase(0, strBegin);
    }
}