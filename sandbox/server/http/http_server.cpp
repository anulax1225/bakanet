#include "http_server.h"

void http_server() 
{
    IpAddress ip("127.0.0.1");
    Socket sock(ip, PORT, IpProtocol::TCP);
    bool running = sock.init() && sock.start(5);
    char input = 'N';
    
    do
    {
        Connection conn = sock.ack();
        if (conn >= 0) 
        {
            std::string http_request(http_handler(sock, conn));
            
            if (http_request == "") continue;
            HttpRequest req = http_parser(http_request);
            log("Http request");
            log("Method " << (int)req.method)
            log("URL " << req.url)
            log("Body " << req.body)
        }
        log("Close?")
        input(input);
    } while (input != 'y');

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