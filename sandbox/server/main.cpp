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
        HttpReponse res(HTTP_RES_200, req.version);
        res.body = "<p>Coucou de /</p>";
        return res;
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



