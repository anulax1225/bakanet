#include <iostream>
#include <string>

#include "bakanet.h"
using namespace Bk::Net;

int main() 
{
    bool running = true;

    IpAddress ip("127.0.0.1");
    Socket sock(ip, 8080, IpProtocol::TCP);
    running = sock.init() && sock.start(50);

    std::string msg = "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/html\r\n\r\n"
                      "<p>Hello World!</p>";
    std::vector<char> data(msg.begin(), msg.end());

    while (running) 
    {   
        Connection conn;
        if ((conn = sock.ack()) > 0) 
        {
            //Sending data step
            sock.write(conn, data);
            close(conn);
        }
    }
	return 0;
}