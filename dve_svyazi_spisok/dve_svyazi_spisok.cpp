#include <iostream>

struct Elements {
	int value;
	Elements* next;
	Elements* predok;
	Elements(int val) {
		value = val;
		next = nullptr;
		predok = nullptr;
	}
};

struct Spisok {
	int size;
	Elements* head;
	Elements* tail;
	Spisok() {
		size = 0;
		head = nullptr;
		tail = nullptr;
	}
	~Spisok() {
		while (head != nullptr) {
			Elements* v = head;
			head = head->next;
			delete v;
		}
	}
	void push_back(int value) {
		if (tail == nullptr) {
			tail = new Elements(value);
			head = tail;
		}
		else {
			Elements* newEl = new Elements(value);
			tail->next = newEl;
			newEl->predok = tail;
			tail = newEl;
		}
		size++;
	}
	void push_front(int value) {
		Elements* newEl = new Elements(value);
		newEl->next = head;
		if (head != nullptr) {
			head->predok = newEl;
		}
		head = newEl;
		size++;
	}
	void pop_back() {
		Elements* cur = tail->predok;
		delete tail;
		tail = cur;
		tail->next = nullptr;
		size--;
	}
	void pop_front() {
		Elements* cur = head->next;
		delete head;
		head = cur;
		size--;
	}

	void print_predok() {
		Elements* cur = tail->predok;
		std::cout << cur->value<<"\n";
	}

	void print() {
		for (Elements* cur = head; cur != nullptr; cur = cur->next) {
			std::cout << cur->value << "\n";
		}
	}
};

int main()
{
    setlocale(LC_ALL, "");
	Spisok a;
	std::cout << "По Добавить элементы\n";
	a.push_back(11);
	a.push_back(21);
	a.push_back(34);
	a.print();
	std::cout << "Предпоследний элемент\n";
	a.print_predok();
	std::cout << "Добавить элемент в начало\n";
	a.push_front(1);
	a.print();
	std::cout << "Удаление\n";
	a.pop_front();
	a.pop_back();
	a.print();
}