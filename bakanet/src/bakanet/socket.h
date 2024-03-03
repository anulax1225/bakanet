#pragma once

#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <cstring>
#include <vector>
#include <string>

#include "ip_address.h"
#include "ip_protocol.h"

namespace Bk::Net {

	using Connection = int;

	class Socket 
	{
	public:
		Socket(IpAddress ip, int port, IpProtocol proto);
		~Socket();

		bool init();
		bool start(int cpt_conn);
		Connection ack();
		bool conn();
		void send(std::vector<char> packet);
		void send(Connection socket, std::vector<char> packet);
		std::vector<char> recv(int size);
		std::vector<char> recv(Connection socket, int size);


	private:
		Socket(int socket_id);

		int socket_id;
		struct sockaddr_in addr;
		IpAddress ip_addr;
		IpProtocol ip_proto;
	};
}