#pragma once

#include <bakanetpch.h>
#include <bakanet/core/ip_address.h>
#include <bakanet/core/socket.h>
#include "http_packet.h"

namespace Bk::Net {
    using RequestHandler = std::function<HttpReponse(HttpRequest& req)>;
    using HttpMethodArray = std::unordered_map<std::string, RequestHandler>;
    using RadixTree = Type::Trie<std::string, HttpMethodArray>;
    using ThreadPool = std::vector<std::thread>;
    
    class HttpServer 
    {
        public:
            HttpServer(IpAddress ip, int port);
            ~HttpServer() = default;
            void start();
            void get(std::string url, RequestHandler req_handler);
            RadixTree radix;
        private:
            std::unique_ptr<Socket> socket;
            ThreadPool threads;

            HttpRequest recv_request(Socket& conn);
            void send_reponse(Socket& conn, HttpReponse res);
            void route_request(Socket& conn, HttpRequest req);
    };
}