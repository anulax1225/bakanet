#include <iostream>
#include <string>

#include "bakanet.h"
using namespace Bk::Net;

int main()
{
    IpAddress ip("127.0.0.1");
    Socket sock(ip, 8080, IpProtocol::TCP);

    bool status = sock.conn();
    if(!status) perror("Couldn't connect.");

    std::string msg = "GET / HTTP/1.1\r\n";
    std::vector<char> data(msg.begin(), msg.end());

    sock.write(data);

    std::vector<char> r_data;
    while((r_data = sock.recv(1024)).size())
    {
        log(r_data.size())
        std::string data_to_str(r_data.begin(), r_data.end());
        log(data_to_str)
    }
    return 0;
}