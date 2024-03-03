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
    log(dns_lookup("edus2.rpn.ch", IpVersion::IPv4)[0])

    IpAddress ip("127.0.0.1");
    Socket sock(ip, 80, IpProtocol::TCP);

    if(!sock.conn()) {
        perror("Couldn't connect to the end point.");
        exit(1);
    }

    Packet packet;
    std::string str("GET / HTTP/1.1\r\n\r\n");
    
    packet.push<char>(str.c_str(), str.length());
    sock.send(packet.payload);
}