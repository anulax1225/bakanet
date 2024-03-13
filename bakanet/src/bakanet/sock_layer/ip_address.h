#pragma once

#include <bakanetpch.h>
#include "ip_version.h"

namespace Bk::Net {
	class IpAddress 
	{
	public:
		IpAddress(std::string ip, IpVersion ipv = IpVersion::IPv4);		
		void* get_data();
		std::string str;
		IpVersion version;
	};
}