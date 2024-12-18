#include <iostream>

int main(int ind, char** val)
{
    setlocale(0, "");
    std::cout << "Кол-во элементов: \n";
    std::cout << ind << '\n';
    for (int i = 0; i < strlen(val[1]); i++) {
        if (i < 3) {

        }
        std::cout << "Часы: " << val[0] << "\n";
        
        std::cout << "Минуты: " << val[1] << "\n";
        std::cout << "Секунды: " << val[2] << "\n";
    }

    std::cout << "День: " << val[3] << "\n";
    std::cout << "Месяц: " << val[4] << "\n";
    std::cout << "Год: " << val[5] << "\n";
}
