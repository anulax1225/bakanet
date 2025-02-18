#pragma once

#include <bakanetpch.h>
#include <bakanet/core/ip_address.h>
#include <bakatools/thread/task_pool.h>
#include <bakanet/core/socket.h>
#include "packet.h"

namespace Bk::Net {
    using RequestHandler = std::function<HttpReponse(HttpRequest& req)>;
    using HttpMethodArray = std::unordered_map<std::string, RequestHandler>;
    using RadixTree = Type::Trie<std::string, HttpMethodArray>;
    
    class HttpServer 
    {
        public:
            HttpServer(IpAddress ip, int port);
            ~HttpServer();
            void start();
            void get(std::string url, RequestHandler req_handler);
            void post(std::string url, RequestHandler req_handler);
            void del(std::string url, RequestHandler req_handler);
            void put(std::string url, RequestHandler req_handler);

        private:
            Socket* socket;
            ThreadPool pool;
            RadixTree radix;

            HttpRequest recv_request(Socket* conn);
            void send_reponse(Socket* conn, HttpReponse res);
            void route_request(Socket* conn, HttpRequest req);
    };
}