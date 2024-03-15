#pragma once

#include <bakanetpch.h>
#include <bakanet/sock_layer/ip_address.h>
#include <bakanet/sock_layer/packet.h>
#include <bakanet/sock_layer/socket.h>
#include "http_packet.h"

namespace Bk::Net {
    class HttpServer 
    {
        using ThreadPool = std::vector<std::thread>;
        using RequestHandler = std::function<HttpReponse(HttpRequest& req)>;
        public:
            HttpServer(IpAddress ip, int port);
            ~HttpServer() = default;
            void start();
            void get(std::string url, RequestHandler req_handler) { req_mapper.insert({ url, req_handler }); }
        private:
            std::unique_ptr<Socket> socket;
            std::unordered_map<std::string, RequestHandler> req_mapper;
            ThreadPool threads;

            HttpRequest recv_request(Socket& conn);
            void send_reponse(Socket& conn, HttpReponse res);
            void route_request(Socket& conn, HttpRequest req);
    };
}