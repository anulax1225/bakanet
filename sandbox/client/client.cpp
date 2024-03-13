#include <sstream>
#include "../commun.h"

using namespace Bk::Net;

void http_client();

int main()
{
    http_client();
    return 0;
}

void http_client()
{
    IpAddress ip("127.0.0.1");
    Socket sock(ip, PORT, IpProtocol::TCP);

    if(!sock.conn()) 
    {
        perror("Couldn't connect to the end point.");
        exit(1);
    }

    Packet packet;
    std::string str = "GET / HTTP/1.1 \r\n"
                      "Host: 127.0.0.1:10001 \r\n\r\n"
                      "Body jylkdkjlkjlkjlkjlkj"; 
    
    packet.push<char>(str.c_str(), str.length());
    sock.send(packet.payload);
}