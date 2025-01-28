#include <iostream>

template <typename T1, typename T2>
struct is_symb {
    static const bool val = false;
};

template<typename T1>
struct is_symb<T1, T1> {
    static const bool val = true;
};

int main()
{
    std::cout << is_symb<int, void>::val;
    
    return 0;
}
