#include "http_server.h"
namespace Bk::Net {
    HttpServer::HttpServer(IpAddress ip, int port) 
    {
        Bk::Log::init("BAKANET");
        BK_CORE_INFO("NEW SERVER");
        socket = Socket::create(ip, port, IpProtocol::TCP);
        radix = RadixTree();
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
    
    void HttpServer::get(std::string url, RequestHandler req_handler)
    {
        RadixTree* tree;
        Tools::string_trim(url, " /");
        auto splits = Tools::string_split(url, "/");
        if (tree = radix.get_node(splits->data(), splits->size())) tree->value["GET"] = req_handler;
        else radix.add_nodes(splits->data(), splits->size(), HttpMethodArray({{ "GET", req_handler }}));
    }

    HttpRequest HttpServer::recv_request(Socket& conn)
    {
        Packet req;
        std::vector<char> data;
        do
        {
            data = conn.obtain(1024);
            req.append_data(data);
        } while(data.size() >= 1024);
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
        std::string url = std::string(req.url);
        Tools::string_trim(url, " /");
        Tools::string_to_upper(req.method);
        auto urls = Tools::string_split(url, "/");
        auto handlers = radix.get_node(urls->data(), urls->size());
        if (handlers && (handlers->value.find(req.method) != handlers->value.end())) { send_reponse(conn, handlers->value[req.method](req)); }
        else send_reponse(conn, HttpReponse(HTTP_RES_404, "HTTP/1.1"));
    }
}