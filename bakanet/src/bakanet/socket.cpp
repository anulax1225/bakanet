#include "socket.h"
#include <iostream>

namespace Bk::Net {
	Socket::Socket(IpAddress ip, int port,IpProtocol proto)
	: ip_addr(ip), ip_proto(proto)
	{
		//Socket creation step
		if ((socket_id = socket((int)ip_addr.version, (int)ip_proto, 0)) < 0) 
		{
	        perror("socket failed");
	        exit(EXIT_FAILURE);
	    }
	    addr.sin_addr = ip_addr.bytes;
		addr.sin_family = (int)ip_addr.version;
    	addr.sin_port = htons(port);
	}

	Socket::~Socket()
	{
		close(socket_id);
	}

	bool Socket::init()
	{
	    //Binding step
		int status;
	    if ((status = bind(socket_id, (struct sockaddr*)&addr, sizeof(addr)) < 0)) 
	    {
			perror("bind failed");
	      	return false;
	    }
	    return true;
	}

	bool Socket::start(int cpt_conn)
	{
	    //Listening step
	    if (listen(socket_id, cpt_conn) < 0) 
	    {
	    	return false;
	    }
	    return true;
	}

	Connection Socket::ack()
	{
		
		socklen_t addrlen = sizeof(addr);
		return accept(socket_id, (struct sockaddr*)&addr, &addrlen);
	}

	bool Socket::conn()
	{
		if (connect(socket_id, (struct sockaddr*)&addr, sizeof(addr)) < 0) 
		{
	        return false;
    	}
    	return true;
	}

	void Socket::send(std::vector<char> packet)
	{
		write(socket_id, packet.data(), packet.size());
	}

	void Socket::send(Connection conn, std::vector<char> packet)
	{
		write(conn, packet.data(), packet.size());
	}

	std::vector<char> Socket::recv(int size)
	{
		std::vector<char> buffer;
		buffer.resize(size);
		int status = read(socket_id, buffer.data(), buffer.size() - 1);
		return status > 0 ? buffer : std::vector<char>();
	}

	std::vector<char> Socket::recv(Connection conn, int size)
	{
		std::vector<char> buffer;
		buffer.resize(size);
		int status = read(conn, buffer.data(), buffer.size() - 1);
		return status > 0 ? buffer : std::vector<char>();
	}
}