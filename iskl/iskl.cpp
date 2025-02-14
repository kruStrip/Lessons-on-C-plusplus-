//#include <iostream>
//#include <exception>
//
//class my_exeption : public std::exception {
//protected:
//    const char* error;
//public:
//    my_exeption(const char* error = "sdfsf") : error(error) {};
//    my_exeption(my_exeption const& other) : error(other.error) {};
//    ~my_exeption() = default;
//
//    const char* what() const noexcept override {
//        return error;
//    }
//};
//
//int foo(int i) {
//    if (i == 0) throw my_exeption("Argument is zero");
//
//    return 1.0 / i;
//}
//
//int main()
//{
//    try
//    {
//        foo(0);
//    }
//    catch (std::exception const& e)
//    {
//        std::cout << e.what();
//    }
//
//    return 0;
//}
