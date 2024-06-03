#pragma once

#include <bakanetpch.h>

namespace Bk::Net {
	enum class IpProtocol 
	{
		TCP = SOCK_STREAM,
		UCP = SOCK_DGRAM,
	};
}