#include <iostream>
#include "Books.h"

int main()
{
    int new_price;
    setlocale(0, "");
    Books book("Гоголь", "Колобок", 3000);

    book.print();

    std::cout << "\nВведите новую цену: ";
    std::cin >> new_price;
    book.change_price(new_price);
    book.print();


}

