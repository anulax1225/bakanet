#pragma once

namespace Bk::Net {
	enum class IpVersion
	{
		UNSPEC = AF_UNSPEC,
		IPv4 = AF_INET,
		IPv6 = AF_INET6,
	};
}