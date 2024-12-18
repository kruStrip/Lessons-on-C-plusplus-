#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <windows.h>

struct Data {
    char data[10][10];
    int player;
};

/// <summary>
/// Server
/// </summary>
/// <returns></returns>

int main()
{
    WSADATA d;
    WORD version = MAKEWORD(2, 2);

    int exitCode = WSAStartup(version, &d);

    if (exitCode != 0) {
        return GetLastError();
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == INVALID_SOCKET) {
        std::cerr << "Could not create socket!" << std::endl;
        return WSAGetLastError();
    }
    
    hostent* host = gethostbyname("");
    char* ip = inet_ntoa(*(in_addr*)(*host->h_addr_list));

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(5150);

    std::cout << "Server address: " << ip << ":" << 5150 << std::endl;

    int result = bind(sock, (sockaddr*)&address, sizeof(address));

    if (result != 0) {
        std::cerr << "Could not listen!" << std::endl;
        closesocket(sock);
        return WSAGetLastError();
    }

    result = listen(sock, 2);

    if (result != 0) {
        std::cerr << "Could not listen!" << std::endl;
        closesocket(sock);
        return WSAGetLastError();
    }

    SOCKET client1 = accept(sock, nullptr, nullptr);

    std::cout << "Client 1 connected\n";
    int player1 = 1;
    send(client1, (char*)&player1, sizeof(int), 0);

    SOCKET client2 = accept(sock, nullptr, nullptr);
    int player2 = 2;
    send(client2, (char*)&player2, sizeof(int), 0);

    std::cout << "Client 2 connected\n";

    {
        Data data{};
        COORD a;
        int hod = 1;
        recv(client1, (char*)&data, sizeof(Data), 0);
        send(client1, (char*)&hod, )
        send(client2, (char*)&data, sizeof(int), 0);
        recv(client2, (char*)&data, sizeof(Data), 0);
    }
    closesocket(sock);

    WSACleanup();

    return 0;
}