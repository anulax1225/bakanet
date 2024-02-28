#pragma once

#include <sys/socket.h>

namespace Bk::Net {
	enum class IpVersion
	{
		IPv4 = AF_INET,
		IPv6 = AF_INET6,
	};
}