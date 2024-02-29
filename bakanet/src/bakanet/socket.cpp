#include "socket.h"
#include <iostream>

namespace Bk::Net {

	std::vector<std::string> dns_lookup(const std::string &host_name, IpVersion ipv = IpVersion::IPv4)
	{
	    std::vector<std::string> output;
	 
	    struct addrinfo hints, *res, *p;
	    int status, ai_family;
	    char ip_address[INET6_ADDRSTRLEN];
	 
	    ai_family = (int)ipv;
	    memset(&hints, 0, sizeof hints);
	    hints.ai_family = ai_family; 
	    hints.ai_socktype = SOCK_STREAM;
	 
	    if ((status = getaddrinfo(host_name.c_str(), NULL, &hints, &res)) != 0) {
	        //cerr << "getaddrinfo: "<< gai_strerror(status) << endl;
	        return output;
	    }
	 
	    for(p = res;p != NULL; p = p->ai_next) {
	        void *addr;
	        if (p->ai_family == AF_INET) { // IPv4
	            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
	            addr = &(ipv4->sin_addr);
	        } else { // IPv6
	            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
	            addr = &(ipv6->sin6_addr);
	        }
	 
	        // convert the IP to a string
	        inet_ntop(p->ai_family, addr, ip_address, sizeof ip_address);
	        output.push_back(ip_address);
	    }
	 
	    freeaddrinfo(res); // free the linked list
	 
	    return output;
	}

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
	    if (bind(socket_id, (struct sockaddr*)&addr, sizeof(addr)) < 0) 
	    {
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

	void Socket::write(std::vector<char> packet)
	{
		send(socket_id, packet.data(), packet.size(), 0);
	}

	void Socket::write(Connection conn, std::vector<char> packet)
	{
		send(conn, packet.data(), packet.size(), 0);
	}

	std::vector<char> Socket::recv(int size)
	{
		std::vector<char> buffer;
		buffer.resize(size);
		int status = read(socket_id, buffer.data(), buffer.size() - 1);
		return status ? buffer : std::vector<char>(0);
	}

	std::vector<char> Socket::recv(Connection conn, int size)
	{
		std::vector<char> buffer;
		buffer.resize(size);
		int status = read(conn, buffer.data(), buffer.size() - 1);
		return status ? buffer : std::vector<char>(0);
	}
}