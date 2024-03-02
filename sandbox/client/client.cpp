#include "../commun.h"

using namespace Bk::Net;

int main()
{
    log(dns_lookup("edus2.rpn.ch", IpVersion::IPv4)[0])

    IpAddress ip("127.0.0.1");
    Socket sock(ip, 9000, IpProtocol::TCP);

    if(!sock.conn()) {
        perror("Couldn't connect to the end point.");
        exit(1);
    }

    Packet packet, meta;
    std::string str("Hello world");
    
    packet.push<char>(str.c_str(), str.length());
    meta.push<int>(packet.size());

    sock.write(meta.payload);
    sock.write(packet.payload);
    return 0;
}