#pragma once

#include <bakanetpch.h>
#include "ip_address.h"
#include "ip_protocol.h"
#include "socket_options.h"

namespace Bk::Net {

	using Connection = int;

	class Socket 
	{
		public:
			virtual ~Socket() {}

			virtual bool init() = 0;
			virtual bool start(int cpt_conn) = 0;
			virtual Socket* ack() = 0;
			virtual bool conn() = 0;
			virtual bool hasConnection(int seconds = 0, int microseconds = 0) = 0;


			virtual int get_raw_socket() = 0;
			virtual const std::string get_ip() = 0;

			virtual void emit(std::vector<char> packet) = 0;
			virtual std::vector<char> obtain(int size) = 0;
			
			template<typename T>
			static bool set_option(Socket& socket, OptionLayer level, SocketOption option_name, const T* option_value) { return setsockopt(socket.get_raw_socket(), (int)level, (int)option_name, (void*)option_value, sizeof(T)) == 0 ? true : false; }

			static Socket* create(IpAddress ip, int port, IpProtocol proto);
		protected:	
			static Socket* create(int id, IpVersion ver, IpProtocol proto);
	};
}