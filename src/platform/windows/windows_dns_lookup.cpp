#include <bakanet/core/dns_lookup.h>

namespace Bk::Net {
	std::vector<std::string> dns_lookup(const std::string& host_name, IpVersion ipv)
	{
		std::vector<std::string> output;
		struct addrinfo hints, *res, *p;
		char ip_address[INET6_ADDRSTRLEN];
		memset(&hints, 0, sizeof hints);
		hints.ai_family = (int)ipv;
		hints.ai_socktype = SOCK_STREAM;

		if (getaddrinfo(host_name.c_str(), NULL, &hints, &res) != 0)
		{
			output.push_back("");
			return output;
		}

		for (p = res;p != NULL; p = p->ai_next)
		{
			void* addr;
			if (p->ai_family == AF_INET)
			{
				struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
				addr = &(ipv4->sin_addr);
			}
			else
			{
				struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)p->ai_addr;
				addr = &(ipv6->sin6_addr);
			}
			inet_ntop(p->ai_family, addr, ip_address, sizeof ip_address);
			output.push_back(ip_address);
		}

		freeaddrinfo(res); // free the linked list

		return output;
	}
}