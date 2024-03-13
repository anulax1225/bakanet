#pragma once

#include <bakanetpch.h>
#include "ip_address.h"
#include "ip_protocol.h"

namespace Bk::Net {

	using Connection = int;

	class Socket 
	{
	public:
		virtual ~Socket() {}

		virtual bool init() = 0;
		virtual bool start(int cpt_conn) = 0;
		virtual Connection ack() = 0;
		virtual bool conn() = 0;
		virtual void emit(std::vector<char> packet) = 0;
		virtual void emit(Connection socket, std::vector<char> packet) = 0;
		virtual std::vector<char> obtain(int size) = 0;
		virtual std::vector<char> obtain(Connection socket, int size) = 0;

		static std::unique_ptr<Socket> Create(IpAddress ip, int port, IpProtocol proto);
	};
}