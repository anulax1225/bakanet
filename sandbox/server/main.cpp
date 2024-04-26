#include <bakatools.h>
#include <bakanet.h>

#define PORT 8080

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
    server.post("/home/", [](HttpRequest& req)
    {
        HttpReponse res(HTTP_RES_200, "HTTP/1.1");
        res.body = "Success";
        BK_INFO("\n{0}\n{1}", req.body, res.to_string());
        return res;
    });
    server.start();
    return 0;
}



