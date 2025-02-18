#include <iostream>
#include "Magaginchik.h"

int main()
{
    setlocale(0, "");
    int var;
    Magaginchik magaz;

    while (true) {
        std::cout <<
            R"(Выберите вариант : 
1 - Посмотреть список покупателей,
2 - Посмотреть список товаров,
3 - Посмотреть список работников,
4 - Добавить клиента

Вариант: )";
        std::cin >> var;

        switch (var)
        {
        case 1:
            magaz.list_clients();
            break;
        case 4: {
            std::string client;
            std::string date;
            std::cout << "Введите ФИО клиента: ";
            std::cin >> client;
            std::cout << "Введите дату: ";
            std::cin >> date;
            magaz.add_client(client, date);
            break;
        }
        default:
            std::cout << "Выберите вариант от 1 - 3";
            break;
        }
    }
}