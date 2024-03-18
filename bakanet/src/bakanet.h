#pragma once 

#include <bakanet/core/ip_address.h>
#include <bakanet/core/packet.h>
#include <bakanet/core/socket.h>

#ifdef BK_PLAFORM_WINDOWS
    #include <platform/windows/windows_socket.h>
#elif BK_PLAFORM_LINUX
    #include <platform/linux/linux_socket.h>
#else
    #error "Plaform not supported"
#endif

#include <bakanet/core/dns_lookup.h>
#include <bakanet/http/http_server.h>