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
            std::unique_ptr<Socket> conn = socket->ack();
            threads.push_back(std::thread([this](std::unique_ptr<Socket> conn) 
            {
                route_request(*conn, recv_request(*conn));
            }, std::move(conn)));
        } 
    }

    HttpRequest HttpServer::recv_request(Socket& conn)
    {
        Packet req;
        bool reading = true;
        while(reading)
        {
            auto data = conn.obtain(1024);
            req.append_data(data);
            reading = data.size() >= 1024;
        }
        int req_size = req.size();
        if (req_size) return HttpRequest(std::string(req.pull<char>(req_size).release(), req_size));
        return HttpRequest("", "", "");
    }

    void HttpServer::send_reponse(Socket& conn, HttpReponse res)
    {
        Packet res_packet;
        std::string str_res = res.to_string();
        res_packet.push<char>(str_res.c_str(), str_res.length());
        conn.emit(res_packet.payload);
    }

    void HttpServer::route_request(Socket& conn, HttpRequest req)
    {
        if(req_mapper[req.url]) send_reponse(conn, req_mapper[req.url](req));
        else send_reponse(conn, HttpReponse(HTTP_RES_404, "HTTP/1.1"));
    }
}