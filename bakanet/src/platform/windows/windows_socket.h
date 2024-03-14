#pragma once

#include <bakanet/sock_layer/socket.h>

namespace Bk::Net {
    class WindowsSocket : public Socket
    {
    public:
        static int socket_count;

        WindowsSocket(IpAddress ip, int port, IpProtocol proto);
        WindowsSocket(int id, IpVersion ver, IpProtocol proto);
        virtual ~WindowsSocket();

        bool init() override;
        bool start(int cpt_conn) override;
        Connection ack() override;
        bool conn() override;

        int get_raw_socket() override { return id; }

        void emit(std::vector<char> packet) override;
        std::vector<char> obtain(int size) override;

    private:
        Connection id;
        struct sockaddr addr;
        IpAddress ip_addr;
        IpProtocol ip_proto;
        bool main;
    };
}