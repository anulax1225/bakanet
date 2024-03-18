#include <bakanet.h>

#define PORT 8000

using namespace Bk::Net;

int main() 
{
    IpAddress ip;
    HttpServer server(ip, PORT);
    server.get("/", [](HttpRequest req) 
    {
        HttpReponse res(HTTP_RES_200, req.version);
        res.body = "<p>Hello World! " + req.url + "</p>";
        return res;
    });

    server.get("/home/", [](HttpRequest req) 
    {
        HttpReponse res(HTTP_RES_200, req.version);
        res.body = "<p>Hello World! " + req.url + "</p>";
        return res;
    });

    server.start();
    return 0;
}



