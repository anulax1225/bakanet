#include "linux_socket.h"
#include <iostream>

namespace Bk::Net {
	LinuxSocket::LinuxSocket(IpAddress ip, int port, IpProtocol proto)
	: ip_addr(ip), ip_proto(proto)
	{
		//LinuxSocket creation step
		if ((socket_id = socket((int)ip_addr.version, (int)ip_proto, 0)) < 0) 
		{
	        perror("socket failed");
	        exit(EXIT_FAILURE);
	    }
	    addr.sin_addr = ip_addr.get_data();
		addr.sin_family = (int)ip_addr.version;
    	addr.sin_port = htons(port);
	}

	LinuxSocket::~LinuxSocket()
	{
		close(socket_id);
	}

	bool LinuxSocket::init()
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

	bool LinuxSocket::start(int cpt_conn)
	{
	    //Listening step
	    if (listen(socket_id, cpt_conn) < 0) 
	    {
	    	return false;
	    }
	    return true;
	}

	Connection LinuxSocket::ack()
	{
		
		socklen_t addrlen = sizeof(addr);
		return accept(socket_id, (struct sockaddr*)&addr, &addrlen);
	}

	bool LinuxSocket::conn()
	{
		if (connect(socket_id, (struct sockaddr*)&addr, sizeof(addr)) < 0) 
		{
	        return false;
    	}
    	return true;
	}

	void LinuxSocket::emit(std::vector<char> packet)
	{
		write(socket_id, packet.data(), packet.size());
	}

	void LinuxSocket::emit(Connection conn, std::vector<char> packet)
	{
		write(conn, packet.data(), packet.size());
	}

	std::vector<char> LinuxSocket::obtain(int size)
	{
		std::vector<char> buffer;
		buffer.resize(size);
		int status = read(socket_id, buffer.data(), buffer.size() - 1);
		return status > 0 ? buffer : std::vector<char>();
	}

	std::vector<char> LinuxSocket::obtain(Connection conn, int size)
	{
		std::vector<char> buffer;
		buffer.resize(size);
		int read_size = read(conn, buffer.data(), buffer.size() - 1);
		buffer.resize(read_size);
		return buffer;
	}

	std::unique_ptr<Socket> Socket::Create(IpAddress ip, int port, IpProtocol proto)
	{
		return std::unique_ptr<Socket>(new LinuxSocket(ip, port, proto));
	}
}