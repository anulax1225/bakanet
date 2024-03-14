#include "http_server.h"
namespace Bk::Net {
    HttpServer::HttpServer(IpAddress ip, int port) 
    {
        socket = Socket::create(ip, port, IpProtocol::TCP);
    }

    void HttpServer::start()
    {
        bool running = socket->init() && socket->start(5);
        while (running)
        {
            log("BEFORE")
            Connection conn = socket->ack();
            if(conn >= 0)
            {
                log("AFTER")
                route_request(conn, recv_request(conn));
                closesocket(conn);
            }

        } 
    }

    HttpRequest HttpServer::recv_request(Connection conn)
    {
        Packet req;
        bool reading = true;
        while(reading)
        {
            auto data = socket->obtain(conn, 1024);
            int size = data.size();
            log("SIZE " << data.size())
            req.append_data(data);
            reading = data.size() >= 1024;
        }
        int req_size = req.size();
        if (req_size) return HttpRequest(std::string(req.pull<char>(req_size).release(), req_size));
        return HttpRequest("", "", "");
    }

    void HttpServer::send_reponse(Connection conn, HttpReponse res)
    {
        Packet res_packet;
        std::string str_res = res.to_string();
        res_packet.push<char>(str_res.c_str(), str_res.length());
        socket->emit(conn, res_packet.payload);
    }

    void HttpServer::route_request(Connection conn, HttpRequest req)
    {
        log("to string")
        log(req.to_string())
        if(req_mapper[req.url]) send_reponse(conn, req_mapper[req.url](req));
        else send_reponse(conn, HttpReponse(HTTP_RES_404, "HTTP/1.1"));
    }
}