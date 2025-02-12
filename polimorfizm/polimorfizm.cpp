#include <iostream>
#include "animal.h"

int main()
{
    setlocale(0, "");
    std::string option;
    std::cin >> option;
    Animal* a = nullptr;

    if (option == "dog") {
        a = new Dog("Barbos");
    }
    else if (option == "cat") {
        a = new Cat("Mysik");
    }
    else if (option == "catdog") {
        a = new Catdog("Bulldog", "Vasya");
    }
    else {
        std::cerr << "Ошибкаа!!!";
        return 0;
    }
    
    a->say();
    delete a;
    return 0;

}
