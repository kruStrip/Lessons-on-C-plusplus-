#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define c(x) (char*)&x, sizeof(x)

#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <string>

struct Data_cl1 {
    char data[10][10];
    int player;
    std::string hod;
    std::string status;
    int y;
    char x;
};
struct Data_cl2 {
    char data[10][10];
    int player;
    std::string hod;
    std::string status;
    int y;
    char x;
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

    std::string status = "Wait";
    send(client1, c(status), 0);
    send(client2, c(status), 0);
    {
        Data_cl1 data_cl1{};
        Data_cl2 data_cl2{};
        COORD a;
        std::string hod = "Можна ходить";
        send(client1, c(hod), 0);
        hod = "Незя ходить";
        send(client2, c(hod), 0);
        recv(client1, (char*)&data_cl1, sizeof(Data_cl1), 0);
        recv(client2, (char*)&data_cl2, sizeof(Data_cl2), 0);

        while ((data_cl1.status != "Готов") && (data_cl2.status != "Готов")) {
            Sleep(300);
            recv(client1, c(data_cl1.status), 0);
            recv(client2, c(data_cl2.status), 0);
        }

        data_cl1.status = "Игра!";
        data_cl2.status = "Игра!";
        send(client1, c(data_cl1.status), 0);
        send(client2, c(data_cl2.status), 0);

        while (data_cl1.status != "Победа" || data_cl1.status != "Поражение") {
            if (data_cl1.hod == "Походил") {
                data_cl1.hod = "Незя ходить";
                data_cl2.hod = "Можна ходить";
                send(client1, c(data_cl1.hod), 0);
                send(client2, c(data_cl2.hod), 0);
            }
            else if (data_cl2.hod == "Походил") {
                data_cl2.hod = "Незя ходить";
                data_cl1.hod = "Можна ходить";
                send(client2, c(data_cl2.hod), 0);
                send(client1, c(data_cl1.hod), 0);
                recv(client1, c(data_cl1.status), 0);
            }
            else {
                Sleep(300);
                recv(client2, c(data_cl2.hod), 0);
                recv(client1, c(data_cl1.hod), 0);
            }
        }
    }
    closesocket(sock);

    WSACleanup();

    return 0;
}