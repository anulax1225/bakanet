#pragma once

#include <bakanet/sock_layer/socket.h>

namespace Bk::Net {
	class LinuxSocket : public Socket
	{
        public:
            LinuxSocket(IpAddress ip, int port, IpProtocol proto);
            virtual ~LinuxSocket();

            bool init() override;
            bool start(int cpt_conn) override;
            Connection ack() override;
            bool conn() override;

            int get_raw_socket() override { return socket_id; }

            void emit(std::vector<char> packet) override;
            void emit(Connection socket, std::vector<char> packet) override;
            std::vector<char> obtain(int size) override;
            std::vector<char> obtain(Connection socket, int size) override;

        private:
            Connection socket_id;
            struct sockaddr_in addr;
            IpAddress ip_addr;
            IpProtocol ip_proto;
	};
}