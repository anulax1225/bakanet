#pragma once

#include <sys/socket.h>

namespace Bk::Net {
	enum class IpProtocol 
	{
		TCP = SOCK_STREAM,
		UCP,
	};
}