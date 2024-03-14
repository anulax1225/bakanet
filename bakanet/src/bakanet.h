#pragma once 

#include <bakanet/sock_layer/ip_address.h>
#include <bakanet/sock_layer/packet.h>
#include <bakanet/sock_layer/socket.h>

#ifdef BK_PLAFORM_WINDOWS
    #include <platform/windows/windows_socket.h>
#elif BK_PLAFORM_LINUX
    #include <platform/linux/linux_socket.h>
#else
    #error "Plaform not supported"
#endif

#include <bakanet/sock_layer/dns_lookup.h>
#include <bakanet/http/http_server.h>