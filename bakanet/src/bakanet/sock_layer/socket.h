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

		virtual int get_raw_socket() = 0;

		virtual void emit(std::vector<char> packet) = 0;
		virtual void emit(Connection socket, std::vector<char> packet) = 0;
		virtual std::vector<char> obtain(int size) = 0;
		virtual std::vector<char> obtain(Connection socket, int size) = 0;
		virtual std::vector<char> obtain() = 0;
		virtual std::vector<char> obtain(Connection socket) = 0;
		
		template<typename T>
		static bool set_option(Socket& socket, int level, int option_name, const T* option_value)
		{
			int status = setsockopt(socket.get_raw_socket(), level, option_name, (void*)option_value, sizeof(T));
			log(status)
			return status == 0 ? true : false;
		}

		static std::unique_ptr<Socket> create(IpAddress ip, int port, IpProtocol proto);
	};
}