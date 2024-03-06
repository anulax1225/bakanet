#include "../commun.h"

using namespace Bk::Net;

enum class HttpMethod
{
    NONE = 0,
    GET = 1,
    POST = 2,
    PUT = 3,
    DELETE = 4,
};

void http_server();
std::string http_handler(Socket& sock, Connection conn);
void http_parser(std::string req);
HttpMethod resolve_methode(std::string method);
std::unique_ptr<std::vector<std::string>> string_split(std::string s, std::string delimiter);
std::string string_trim(const std::string& str, const std::string& whitespace = " ");

int main() 
{
    http_server();
    return 0;
}

void http_server() 
{
    IpAddress ip("127.0.0.1");
    Socket sock(ip, PORT, IpProtocol::TCP);
    bool running = sock.init() && sock.start(5);

    auto trimed_str = string_trim(std::string(" Hello "));
    log(trimed_str)
    while (running)
    {
        Connection conn = sock.ack();
        if (conn >= 0) 
        {
            std::string http_request(http_handler(sock, conn));
            http_parser(http_request);
        }
    }

}

std::string http_handler(Socket& sock, Connection conn) 
{
    Packet req;
    bool reading = true;
    while(reading)
    {
        std::vector<char> raw_data;
        raw_data = sock.recv(conn, 4);
        reading = req.append_data(raw_data);
    }

    close(conn);

    int req_size = req.size();
    std::unique_ptr<char[]> req_test = req.pull<char>(req_size);

    if (req_size) return std::string(req_test.release(), req_size);
    return "";
}

void http_parser(std::string req)
{
    auto lines = string_split(req, "\r\n");
    for (auto line : *lines)
    {
        auto param = string_split(line, ":");

    }

}


HttpMethod resolve_methode(std::string method)
{
    if (method == "GET") return HttpMethod::GET;
    else if (method == "POST") return HttpMethod::POST;
    else if (method == "PUT") return HttpMethod::PUT;
    else if (method == "DELETE") return HttpMethod::DELETE;
    else return HttpMethod::NONE;
}

std::unique_ptr<std::vector<std::string>> string_split(std::string s, std::string delimiter)
{
    std::unique_ptr<std::vector<std::string>> splits(new std::vector<std::string>(0));
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        splits->push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    splits->push_back(s);
    return splits;
}

std::string string_trim(const std::string& str, const std::string& whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}