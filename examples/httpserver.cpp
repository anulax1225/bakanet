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
        HttpReponse res(HTTP_RES_200, req.version);
        res.body = "<h1>Bakanet</h1>";
        res.body += "<p>Working http server</p>";
        res.body += "\n<p>URL /</p>";
        return res;
    });
    server.start();
    return 0;
}