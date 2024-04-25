#include <bakatools.h>
#include <bakanet.h>

#define PORT 80

using namespace Bk::Net;

int main() 
{
    Bk::Log::init("Bakanet");
    IpAddress ip;
    HttpServer server(ip, PORT);
    server.get("/", [](HttpRequest& req)
    {
        BK_INFO("URL /");
        HttpReponse res(HTTP_RES_200, req.version);
        res.body = "<p>Coucou de /</p>";
        return res;
    });
    server.get("/home/", [](HttpRequest& req)
    {
        BK_INFO("URL /home");
        HttpReponse res(HTTP_RES_200, req.version);
        res.body = "<p>Coucou de /home/</p>";
        return res;
    });
    server.start();
    return 0;
}



