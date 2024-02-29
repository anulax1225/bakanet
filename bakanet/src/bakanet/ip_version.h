#pragma once

#include <sys/socket.h>

namespace Bk::Net {
	enum class IpVersion
	{
		UnSpec = AF_UNSPEC,
		IPv4 = AF_INET,
		IPv6 = AF_INET6,
	};
}