#include <iostream>
#include "sub.h"

int main()
{
    StringWrapper str("Aalalalala");

    std::string subs = str[1][5];
    std::cout << subs;

    return 0;
}

