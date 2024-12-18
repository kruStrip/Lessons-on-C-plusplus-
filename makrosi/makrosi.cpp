#include <iostream>

#define pow10(a) (1e##a)
#define plus(a,b) a##b
#define STRUCT(a) struct a {int value;double valuel;};

#ifdef _DEBUG
#define DBG(msg) "\033[101m"<<msg<<"\033[0m" <<"\n" <<__FILE__ << "\n"<<__FUNCTION__;
#else 
#define DBG(msg) " "
#endif

int main()
{
    std::cout << pow10(2)<<"\n";
    std::cout << plus(1, 2)<<"\n";
    std::cout << DBG("ahkjhadsj");
}
