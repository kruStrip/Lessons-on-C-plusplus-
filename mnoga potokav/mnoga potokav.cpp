#include <iostream>
#include <thread>
#include <windows.h>
#include <future>
#include <mutex>

std::mutex m;

void print(const char* str) {
    for (int i = 0; i < 5; i++) {

        Sleep(1000);
        //m.lock(); Блокировка потока через Mutex
        //Начало и автоматичекое отключение блокировки в момент выхода из функции
        std::lock_guard<std::mutex>lock(m);
        std::cout << "String #" << i << "\n";
        //m.unlock(); отключение блокировки
    }


    //return strlen(str);
}

int main()
{
    //int length;

    //лямбда функция
    /*auto func = [&length](const char* str) {
        length = print(str);
        };
    */

    //тож лямбда
    //std::thread thr([&length](const char* str) {length = print(str);}, "Hello, world!");//создание отдельного потока

    //std::future<int> thrf = std::async(std::launch::async, print, "Hello, World!");

    std::thread thr(print, "Hello, World!");
    print("Hello, World!");

    /*for (int i = 0; i < 10; i++) {
        m.lock();//Блокировка потока через Mutex
        Sleep(1000);
        std::cout << "String #" << i << "\n";
        m.unlock();
    }*/

    thr.join();//Ожидание завершения потока

    //std::cout << "Length of \"Hello world\" is " << thrf.get();
    return 0;
}

