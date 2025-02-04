#include <iostream>
#include <string>
#include <list>

class Student {
    std::string name;
    std::string facylti;
    std::list<int> marks;

public:
    void add(int mark) {
        marks.push_back(mark);
    }
    void delete_mark(int mark) {
        for (auto i = marks.begin(); i != marks.end(); ++i) {
            if (*i == mark) {
                marks.remove(*i);
                return;
            }
        }
    }
    void change_mark(int new_mark, int old_mark) {
        for (auto i = marks.begin(); i != marks.end(); ++i) {
            if (*i == old_mark) {
                *i = new_mark;
            }
        }
    }
    void all_marks() {
        for (auto i = marks.begin(); i != marks.end(); ++i) {
            std::cout << *i << " ";
        }
        std::cout << "\n";
    }
};

int main()
{
    setlocale(0, "");
    int mark;
    int new_mark;
    Student s;
    int var;

    while (true){
        std::cout << "Что сделать?\n 1- Добавить оценку\n 2- Удалить оценку\n 3- Показать все оценки\n 4- Изменить оценку\n Выбор: ";
        std::cin >> var;
        switch (var) {
        case 1:
            std::cout << "Введите какую оценку вы хотите добавить: ";
            std::cin >> mark;
            s.add(mark);
            break;
        case 2:
            std::cout << "Введите какую оценку вы хотите удалить: ";
            std::cin >> mark;
            s.delete_mark(mark);
            break;
        case 3:
            std::cout << "\nВсе оценки: \n";
            s.all_marks();
            break;
        case 4:
            std::cout << "Введите какую оценку вы хотите изменить: ";
            std::cin >> mark;
            std::cout << "Введите новую оценку: ";
            std::cin >> new_mark;
            s.change_mark(new_mark, mark);
            break;
        default:
            std::cout << "\nНеверный ввод\n";
    }
 }
}
