#include <iostream>
#include <Ws2tcpip.h>
#include <WinSock2.h>
#include <tchar.h>


#pragma comment(lib,"WS2_32.lib")

int main()
{
	WSADATA wsaData;
	int err;

    err = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (err != 0)
    {
        std::cout << "Winsock DDL not found!" << std::endl;
        WSACleanup();
        system("pause");
        return 0;
    }

    //client socket
    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == INVALID_SOCKET)
    {
        std::cout << "Invalid client socker: " + WSAGetLastError() << std::endl;
        WSACleanup();
        system("pause");
        return 0;
    }

    //conf socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
    service.sin_port = htons(25580);

    //connect to serv
    if (connect(sock, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
    {
        std::cout << "Failed to connect to the server: " + WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        system("pause");
        return 0;
    }

    //send message to serv
    std::string message = "Hello server!";
    if (send(sock, message.c_str(), message.length(), 0) == SOCKET_ERROR)
    {
        std::cout << "Failed to send messaage to the server: " + WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        system("pause");
        return 0;
    }

    std::cout << "All good :)" << std::endl;
    closesocket(sock);
    WSACleanup();
    system("pause");
    return 0;
}