#include "linux_socket.h"

namespace Bk::Net {
	LinuxSocket::LinuxSocket(int id, IpVersion ver, IpProtocol proto)
	: id(id), ip_proto(proto)
	{
		char myIP[16] = "               ";
		socklen_t len = sizeof(addr);
    	getsockname(id, (struct sockaddr*)&addr, &len);
		inet_ntop((int)ver, &addr, myIP, sizeof(myIP));
		ip_addr = IpAddress(std::string(myIP, 16), ver);
	}

	LinuxSocket::LinuxSocket(IpAddress ip, int port, IpProtocol proto)
	: ip_addr(ip), ip_proto(proto)
	{
		//LinuxSocket creation step
		if ((id = socket((int)ip_addr.version, (int)ip_proto, 0)) < 0) 
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
		close(id);
	}

	bool LinuxSocket::init()
	{
	    //Binding step
		int status;
	    if ((status = bind(id, (struct sockaddr*)&addr, sizeof(addr)) < 0)) 
	    {
			perror("bind failed");
	      	return false;
	    }
	    return true;
	}

	bool LinuxSocket::start(int cpt_conn)
	{
	    //Listening step
	    if (listen(id, cpt_conn) < 0) 
	    {
	    	return false;
	    }
	    return true;
	}

	std::unique_ptr<Socket> LinuxSocket::ack()
	{
		
		socklen_t addrlen = sizeof(addr);
		return std::unique_ptr<Socket>(Socket::create(accept(id, (struct sockaddr*)&addr, &addrlen), ip_addr.version, ip_proto));
	}

	bool LinuxSocket::conn()
	{
		if (connect(id, (struct sockaddr*)&addr, sizeof(addr)) < 0) 
		{
	        return false;
    	}
    	return true;
	}

	void LinuxSocket::emit(std::vector<char> packet)
	{
		write(id, packet.data(), packet.size());
	}

	std::vector<char> LinuxSocket::obtain(int size)
	{
		std::vector<char> buffer;
		buffer.resize(size);
		int read_size = read(id, buffer.data(), buffer.size() - 1);
		buffer.resize(read_size);
		return buffer;
	}
	
	std::unique_ptr<Socket> Socket::create(IpAddress ip, int port, IpProtocol proto)
	{
		return std::unique_ptr<Socket>(new LinuxSocket(ip, port, proto));
	}

	std::unique_ptr<Socket> Socket::create(int id, IpVersion ver, IpProtocol proto)
	{
		return std::unique_ptr<Socket>(new LinuxSocket(id, ver, proto));
	}
}