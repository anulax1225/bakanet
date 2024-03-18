#pragma once 

#include <bakanet/core/ip_address.h>
#include <bakanet/core/packet.h>
#include <bakanet/core/socket.h>

#if defined(BK_PLATFORM_WINDOWS)
    #include <platform/windows/windows_socket.h>
#elif defined(BK_PLATFORM_LINUX)
    #include <platform/linux/linux_socket.h>
#else
    #error "Plaform not supported"
#endif

#include <bakanet/core/dns_lookup.h>
#include <bakanet/http/http_server.h>