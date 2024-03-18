#pragma once

#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <exception>
#include <memory>
#include <cstdint>
#include <cctype>
#include <unordered_map>
#include <functional>
#include <thread>

#define log(str) std::cout << str << "\n";
#define input(ref) std::cin >> ref;

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
    #include <sys/time.h>
#else
    #error "Plaform not supported"
#endif
