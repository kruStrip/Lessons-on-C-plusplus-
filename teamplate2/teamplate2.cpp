#include <iostream>
#include <tuple>
#include <vector>

template <typename First>
void print(First f) {
        std::cout << f << "\n";
}

template <typename First, typename ... Last>
void print(First f, Last ... rest) {
     std::cout << f << " ";
     print(rest...);
}

int main()
{
    print(10, "str", 2.81);

    std::tuple<int, double, std::vector<std::string>> a(10, 2.81, { "true", "false" });

    auto& vec = std::get<2>(a);

    for (int i = 0; i < 3; i++) {
        std::cout << vec[i] << "\n";
    }

    return 0;
}

