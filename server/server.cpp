#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <conio.h>
#include <list>
#include <vector>
#define N 10

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //возвращает

enum Direction {
    up = 1,
    down = -1,
    left = 2,
    right = -2,
    none = 0,
    space = 3
};

struct Data;

void getKey(Data* korabl);

struct Data {
    char data[10][10];
    int player;

    Direction direction;
    std::list<COORD> k1;
    std::list<COORD> k2;
    std::list<COORD> k3;
    std::list<COORD> k4;

    std::vector<std::list<COORD>*> korabliki;

    Data(int playerId) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                data[i][j] = 0;
            }
        }
        player = playerId;
        direction = Direction::none;
        k1 = { { 25, 2 } };
        k2 = { {30, 2}, {30, 3 } };
        k3 = { {35, 2}, { 35, 3 }, {35, 4} };
        k4 = { {40, 2}, { 40, 3 }, {40, 4}, {40, 5} };
        korabliki = { &k1, &k2, &k3, &k4 };
    }

    void output() {
        SetConsoleCursorPosition(console, {0,0});
        std::cout << " ";
        for (int i = 0; i < N; i++) {
            std::cout << ' '<<i;
        }
        for (int i = -1; i < N; i++) {
            if (i > -1) {
                printf("%c", (char)(i + 'A'));
            }
            for (int j = 0; j < N; j++) {
                switch (data[i][j]) {
                case 0:
                    printf("\033[105m%s\033[0m", "  ");
                    break;
                case 1:
                    printf("\033[105m%s\033[0m", "  ");
                    break;
                case 2:
                    printf("\033[105m%s\033[0m", "  ");
                    break;
                case 3:
                    printf("\033[105m%s\033[0m", "  ");
                    break;
                case 4:
                    printf("\033[105m%s\033[0m", "  ");
                    break;
                }
            }
            printf("\n");
        }
    }

    void output_korabli(std::list<COORD> korablik) {
        for (COORD k : korablik) {
            SetConsoleCursorPosition(console, k);
            printf("\033[46m%c\033[0m", '*');
        }
    }

    void move_korabliki(std::list<COORD> *k) {
        while (true) {
            getKey(this);
            if (direction == Direction::space) {
                direction = Direction::none;
                Sleep(300);
                break;
            }
            else if (direction == Direction::right) {
                for (COORD& w : *k) {
                    SetConsoleCursorPosition(console, w);
                    printf("%c", ' ');
                    w.X += 1;
                }
            }
            else if (direction == Direction::up) {
                for (COORD& w : *k) {
                    SetConsoleCursorPosition(console, w);
                    printf("%c", ' ');
                    w.Y -= 1;
                }
            }
            else if (direction == Direction::left) {
                for (COORD& w : *k) {
                    SetConsoleCursorPosition(console, w);
                    printf("%c", ' ');
                    w.X -= 1;
                }
            }
            else if (direction == Direction::down) {
                for (COORD& w : *k) {
                    SetConsoleCursorPosition(console, w);
                    printf("%c", ' ');
                    w.Y += 1;
                }
            }
            direction = Direction::none;
            output();
            for (std::list<COORD>* kor : korabliki) {
                output_korabli(*kor);
            }
            Sleep(300);
        }
    }
};

void getKey(Data* korabl) {
    Direction newDir = Direction::none;
    if (GetAsyncKeyState(VK_UP)) newDir = Direction::up;
    else if (GetAsyncKeyState(VK_LEFT)) newDir = Direction::left;
    else if (GetAsyncKeyState(VK_DOWN)) newDir = Direction::down;
    else if (GetAsyncKeyState(VK_RIGHT)) newDir = Direction::right;
    else if (GetAsyncKeyState(VK_SPACE)) newDir = Direction::space;
    if (newDir == Direction::none) {
        return;
    }

    korabl->direction = newDir;
}

/// <summary>
/// Client
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
        std::cerr << "Could not create socket!"<<std::endl;
        return WSAGetLastError();
    }

    char ip[16];
    std::cout << "Enter server IP address: ";
    std::cin >> ip;
    short port;
    std::cout << "Enter server port: ";
    std::cin >> port;

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);

    int result = connect(sock, (sockaddr*)&address, sizeof(address));

    if (result != 0) {
        std::cerr << "Connection failed!" << std::endl;
        closesocket(sock);
        return WSAGetLastError();
    }

    int playerId;
    recv(sock, (char*)&playerId, sizeof(Data), 0);

    std::cout << "This is player #" << playerId << std::endl;

    {
        //send(sock, (char*)&data, sizeof(Data), 0);
            system("cls");

            Data data(playerId);
            data.output();
            int hod = 0;
            int x;
            char y;
            for (std::list<COORD>* k : data.korabliki) {
                data.output_korabli(*k);
            }
            for (std::list<COORD>* k : data.korabliki) {
                data.move_korabliki(k);
            }
            send(sock, (char*)&data, sizeof(Data), 0);
            recv(sock, (char*)&hod, sizeof(int), 0);
            while (hod == 1) {
                scanf("%c %c", &x, &y);
            }
    }

    closesocket(sock);

    WSACleanup();

    return 0;
}
