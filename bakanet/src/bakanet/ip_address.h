#pragma once

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <exception>
#include <cctype>

#include "ip_version.h"

namespace Bk::Net {
	class IpAddress 
	{
	public:
		IpAddress(const char* ip, IpVersion ipv = IpVersion::IPv4);

		static void from_dns(char* dns);
		
		const char* str;
		in_addr bytes;
		IpVersion version;
	};
}