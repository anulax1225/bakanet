#include "../commun.h"

using namespace Bk::Net;

void http_server();
std::string http_handle(Socket& sock, Connection conn);

int main() 
{
    http_server();
    return 0;
}

void http_server() 
{
    IpAddress ip("127.0.0.1");
    Socket sock(ip, 80, IpProtocol::TCP);
    bool running = sock.init() && sock.start(5);
    while (running)
    {
        Connection conn = sock.ack();
        if (conn >= 0) 
        {
            log(http_handle(sock, conn));
        }
    }
}

std::string http_handle(Socket& sock, Connection conn) 
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