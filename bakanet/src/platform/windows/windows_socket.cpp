#include "windows_socket.h"
#include <iostream>

namespace Bk::Net {
	int WindowsSocket::socket_count = 0;

	WindowsSocket::WindowsSocket(int id, IpVersion ver, IpProtocol proto)
	: id(id), ip_proto(proto), main(false)
	{
		char myIP[16] = "               ";
		socklen_t len = sizeof(addr);
    	getsockname(id, (struct sockaddr*)&addr, &len);
		inet_ntop((int)ver, &addr, myIP, sizeof(myIP));
		ip_addr = IpAddress(std::string(myIP, 16), ver);
	}

	WindowsSocket::WindowsSocket(IpAddress ip, int port, IpProtocol proto)
		: ip_addr(ip), ip_proto(proto), main(true)
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
		if ((id = (int)socket((int)ip_addr.version, (int)ip_proto, 0)) < 0)
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
		if (main && socket_count-- < 1) WSACleanup();
		closesocket(id);
	}

	bool WindowsSocket::init()
	{
		//Binding step
		int status;
		if ((status = bind((SOCKET)id, (struct sockaddr*)&addr, sizeof(addr)) < 0))
		{
			log("bind failed " << WSAGetLastError());
			return false;
		}
		return true;
	}

	bool WindowsSocket::start(int cpt_conn = SOMAXCONN)
	{
		//Listening step
		if (listen(id, cpt_conn) == SOCKET_ERROR) { return false; }
		return true;
	}

	std::unique_ptr<Socket> WindowsSocket::ack()
	{
		socklen_t addrlen = sizeof(addr);
		return Socket::create(accept((SOCKET)id, (struct sockaddr*)&addr, &addrlen), ip_addr.version, ip_proto);
	}

	bool WindowsSocket::conn()
	{
		if (connect(id, (struct sockaddr*)&addr, sizeof(addr)) < 0) { return false; }
		return true;
	}

	void WindowsSocket::emit(std::vector<char> packet)
	{
		send((SOCKET)id, packet.data(), packet.size(), 0);
	}

	std::vector<char> WindowsSocket::obtain(int size)
	{
		log(1)
		std::vector<char> buffer;
		buffer.resize(size);
		log(2)
		int read_size = recv((SOCKET)id, buffer.data(), buffer.size() - 1, 0);
		log(3)
		buffer.resize(read_size);
		return buffer;
	}

	std::unique_ptr<Socket> Socket::create(IpAddress ip, int port, IpProtocol proto)
	{
		return std::unique_ptr<Socket>(new WindowsSocket(ip, port, proto));
	}

	std::unique_ptr<Socket> Socket::create(int id, IpVersion ver, IpProtocol proto)
	{
		return std::unique_ptr<Socket>(new WindowsSocket(id, ver, proto));
	}
}