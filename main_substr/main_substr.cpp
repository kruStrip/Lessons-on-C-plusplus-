#include <iostream>
#include "sub.h"

int main()
{
    StringWrapper str("Aalalalala");

    std::string subs = str[1][10];
    std::cout << subs;

    return 0;
}

