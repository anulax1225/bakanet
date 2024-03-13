#pragma once

#include <cstring>
#include <vector>
#include <string>
#include <exception>
#include <memory>
#include <cstdint>
#include <cctype>
#include <string>

#ifdef BK_PLAFORM_WINDOWS
    #include <Ws2tcpip.h>
    #include <WinSock2.h>
    #include <tchar.h>
    #pragma comment(lib,"WS2_32.lib")
#elif BK_PLAFORM_LINUX
    #include <netinet/in.h>
    #include <stdlib.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #include <netdb.h>
    #include <arpa/inet.h>
#else
    #error "Plaform not supported"
#endif
