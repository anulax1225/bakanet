#include <bakanetpch.h>

namespace Bk::Net {
	enum class OptionLayer 
	{
		IP = IPPROTO_IP,
		IPv6 = IPPROTO_IPV6,
		RawIP = IPPROTO_ICMP,
		TCP = IPPROTO_TCP,
		UDP = IPPROTO_UDP,
		Socket = SOL_SOCKET,
	};

	enum class SocketOption
	{
		Debug = SO_DEBUG,
		Broadcast = SO_BROADCAST,
		ReuseAddr = SO_REUSEADDR,
		KeepAlive = SO_KEEPALIVE,
		Linger = SO_LINGER,
		OutOfBandInline = SO_OOBINLINE,
		SendBuffer = SO_SNDBUF,
		ReceiveBuffer = SO_RCVBUF,
		DontRoute = SO_DONTROUTE,
		ReceiveMin = SO_RCVLOWAT,
		ReceiveTimeOut = SO_RCVTIMEO,
		SendMin = SO_SNDLOWAT,
		SendTimeOut = SO_SNDTIMEO,
	};
}