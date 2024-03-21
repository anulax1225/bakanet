#include <bakatools.h>
#include <bakanet.h>

#define PORT 8000

using namespace Bk::Net;

int main() 
{
    IpAddress ip;
    HttpServer server(ip, PORT);
    server.get("/", [](HttpRequest& req)
    {
        BK_INFO("URL /");
        return HttpReponse("", "");
    });
    server.get("/home/", [](HttpRequest& req)
    {
        BK_INFO("URL /home");
        return HttpReponse("", "");
    });
    server.get("/home", [](HttpRequest& req)
    {
        BK_INFO("URL NEW /home");
        return HttpReponse("", "");
    });
    server.start();
    return 0;
}



