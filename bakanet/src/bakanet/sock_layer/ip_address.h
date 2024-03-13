#pragma once

#include <bakanetpch.h>
#include "ip_version.h"

namespace Bk::Net {
	class IpAddress 
	{
	public:
		IpAddress(std::string ip = "", IpVersion ipv = IpVersion::IPv4)
		: str(ip), version(ipv) { }
		
		struct in_addr get_data();
		std::string str;
		IpVersion version;
	};
}