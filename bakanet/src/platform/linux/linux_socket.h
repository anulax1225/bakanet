#pragma once

#include <bakanet/core/socket.h>

namespace Bk::Net {
	class LinuxSocket : public Socket
	{
        public:
            LinuxSocket(IpAddress ip, int port, IpProtocol proto);
            LinuxSocket(int id, IpVersion ver, IpProtocol proto);
            virtual ~LinuxSocket();

            bool init() override;
            bool start(int cpt_conn) override;
            std::unique_ptr<Socket> ack() override;
            bool conn() override;

            int get_raw_socket() override { return id; }
            const std::string get_ip() override { return ip_addr.str; }

            void emit(std::vector<char> packet) override;
            std::vector<char> obtain(int size) override;

        private:
            Connection id;
            struct sockaddr_in addr;
            IpAddress ip_addr;
            IpProtocol ip_proto;
	};
}