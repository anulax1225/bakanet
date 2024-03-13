#include <cstring>

#include <commun.h>

std::string string_to_upper(std::string& str);
std::unique_ptr<std::vector<std::string>> string_split(std::string s, std::string delimiter, int cpt = -1);
std::string string_trim(const std::string& str, const std::string& whitespace = " ");