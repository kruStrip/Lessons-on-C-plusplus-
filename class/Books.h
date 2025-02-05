#pragma once
#include <iostream>

class Books
{
    std::string author;
    std::string title;
    int price;
public:
    Books(std::string author_, std::string title_, int price_) {
        author = author_;
        title = title_;
        price = price_;
    }
    ~Books() = default;

    void change_price(int new_p) {
        price = new_p;
    }
    void print() {
        std::cout <<"Автор: "<< author<< std::endl;
        std::cout << "Название: " << title << std::endl;
        std::cout << "Цена: " << price << std::endl;
    }

};

