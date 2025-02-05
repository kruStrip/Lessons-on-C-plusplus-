#include <iostream>

class StringWrapper {
    class StringWrapperImpl {
        int ind;
        std::string& strref;

    public:
        StringWrapperImpl(std::string& str, int i) : strref(str) {
            ind = i;
        }
        std::string operator[](int i) {
            std::string substr;
            for (int k = ind; k < i; k++) {
                substr += strref[k];
             
            }
            return substr;
        }
    };
    std::string str_;
public:
    StringWrapper(const char* str) : str_(str) {
    
    };

    StringWrapperImpl operator[](int i) {
        StringWrapperImpl s(str_, i);
        return s;
    }
};