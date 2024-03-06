#include <iostream>
#include <Ws2tcpip.h>
#include <WinSock2.h>
#include <tchar.h>

#pragma comment(lib, "WS2_32.lib")

int main()
{
    WSADATA wsaData;
    int err;

    err = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (err != 0)
    {
        std::cout << "Winsock DLL not found!" << std::endl;
        WSACleanup();
        system("pause");
        return 0;
    }

    //server socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == INVALID_SOCKET)
    {
        std::cout << "Invalid server socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        system("pause");
        return 0;
    }

    //conf socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(25580);

    //bind
    if (bind(sock, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
    {
        std::cout << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        system("pause");
        return 0;
    }

    //listen
    if (listen(sock, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cout << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        system("pause");
        return 0;
    }

    std::cout << "Waiting for connection..." << std::endl;

    //Accept client socket
    SOCKET clientSocket = accept(sock, NULL, NULL);

    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "Accept failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        system("pause");
        return 0;
    }

    std::cout << "Client connected" << std::endl;

    char buffer[256];
    int bytesRead;

    do
    {
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead > 0) 
        {
            buffer[bytesRead] = '\0';
            std::cout << buffer << std::endl;
        }

    } while (bytesRead > 0);

    closesocket(clientSocket);
    closesocket(sock);
    WSACleanup();
    system("pause");

    return 0;
}
