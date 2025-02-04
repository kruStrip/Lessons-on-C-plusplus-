#include <iostream>

class StringWrapper {
    class StringWrapperImpl {
        std::string& strref;
    public:
        std::string operator[](int i) {

        }
    };
    std::string str_;
public:
    StringWrapper(const char* str) : str_(str) {};

    StringWrapperImpl operator[](int i) {

    }
};



