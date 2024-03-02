#include "../commun.h"

using namespace Bk::Net;

int main() 
{
    IpAddress ip("127.0.0.1");
    Socket sock(ip, 9000, IpProtocol::TCP);
    
    bool running = sock.init() && sock.start(50);

    while (running) 
    {   
        Connection conn;
        if ((conn = sock.ack()) > 0) 
        {
            log("New Connection")
            Packet meta_data(sock.recv(conn, 4));
            int length = meta_data.pull<int>();
            if (length > 0)
            {
                Packet data(sock.recv(conn, length + 2));
                log(data.pull<char>(length).release());
            }
            close(conn);
        }
    }
    return 0;
}