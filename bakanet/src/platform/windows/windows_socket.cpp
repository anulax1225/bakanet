#include "windows_socket.h"
#include <iostream>

namespace Bk::Net {
	int WindowsSocket::socket_count = 0;

	WindowsSocket::WindowsSocket(IpAddress ip, int port, IpProtocol proto)
		: ip_addr(ip), ip_proto(proto)
	{
		if (socket_count++ < 1)
		{
			WSADATA wsa_data;
			int err;
			err = WSAStartup(MAKEWORD(2, 2), &wsa_data);
			if (err != 0) 
			{
				log("WSA failed " << WSAGetLastError());
				WSACleanup();
				system("pause");
				exit(EXIT_FAILURE);
			}
		}

		//WindowsSocket creation step
		if ((socket_id = (int)socket((int)ip_addr.version, (int)ip_proto, 0)) < 0)
		{
			log("socket failed " << WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		addr.sin_addr = ip_addr.get_data();
		addr.sin_family = (int)ip_addr.version;
		addr.sin_port = htons(port);
	}

	WindowsSocket::~WindowsSocket()
	{
		WSACleanup();
		closesocket(socket_id);
	}

	bool WindowsSocket::init()
	{
		//Binding step
		int status;
		if ((status = bind(socket_id, (struct sockaddr*)&addr, sizeof(addr)) < 0))
		{
			log("bind failed " << WSAGetLastError());
			return false;
		}
		return true;
	}

	bool WindowsSocket::start(int cpt_conn = SOMAXCONN)
	{
		//Listening step
		if (listen(socket_id, cpt_conn) == SOCKET_ERROR)
		{
			return false;
		}
		return true;
	}

	Connection WindowsSocket::ack()
	{
		socklen_t addrlen = sizeof(addr);
		return accept(socket_id, (struct sockaddr*)&addr, &addrlen);
	}

	bool WindowsSocket::conn()
	{
		if (connect(socket_id, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		{
			return false;
		}
		return true;
	}

	void WindowsSocket::emit(std::vector<char> packet)
	{
		send((SOCKET)socket_id, packet.data(), packet.size(), 0);
	}

	void WindowsSocket::emit(Connection conn, std::vector<char> packet)
	{
		send((SOCKET)conn, packet.data(), packet.size(), 0);
	}

	std::vector<char> WindowsSocket::obtain(int size)
	{
		std::vector<char> buffer;
		buffer.resize(size);
		int read_size = recv((SOCKET)socket_id, buffer.data(), buffer.size() - 1, 0);
		buffer.resize(read_size);
		return buffer;
	}

	std::vector<char> WindowsSocket::obtain(Connection conn, int size)
	{
		std::vector<char> buffer;
		buffer.resize(size);
		int read_size = recv((SOCKET)conn, buffer.data(), buffer.size() - 1, 0);
		buffer.resize(read_size);
		return buffer;
	}

	std::unique_ptr<Socket> Socket::create(IpAddress ip, int port, IpProtocol proto)
	{
		return std::unique_ptr<Socket>(new WindowsSocket(ip, port, proto));
	}
}