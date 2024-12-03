#include <iostream>
#include <vector>

struct Elements {
	int value;
	Elements* next;
	Elements(int val) {
		value = val;
		next = nullptr;
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
	void push_front(int value) {
		Elements* newEl = new Elements(value);
		newEl->next = head;
		if (head == nullptr) {
			tail = newEl;
		}
		head = newEl;
		size++;
	}
	void push_back(int value) {
		if (tail == nullptr) {
			tail = new Elements(value);
			head = tail;
		}
		else {
			Elements* newEl = new Elements(value);
			tail->next = newEl;
			tail = newEl;
		}
		size++;
	}
	void at(int value) {
		int ind = 0;
		for (Elements* cur = head; cur != nullptr; cur = cur->next) {
			if (ind == value) {
				std::cout << cur->value << "\n";
				break;
			}
			ind += 1;
		}
	}
	void insert(int value, int num) {
		int ind = 0;
		for (Elements* cur = head; cur != nullptr; cur = cur->next) {
			if (ind == (value-1)) {
				Elements* newEl = new Elements(num);
				newEl->next = cur->next;
				cur->next = newEl;
				size++;
				break;
			}
			ind += 1;
		}
	}
	void pop_back() {
		for (Elements* cur = head; cur != nullptr; cur = cur->next) {
			if (cur->next == tail) {
				delete tail;
				tail = cur;
				cur->next = nullptr;
				break;
			}
		}
	}
	void pop_front() {
		Elements* cur = head->next;
		delete head;
		head = cur;
	}

	void print() {
		for (Elements* cur = head; cur != nullptr; cur = cur->next) {
			std::cout << cur->value << "\n";
		}
	}
};


int main() {
	setlocale(LC_ALL, "");
	Spisok a;
	std::cout << "По Добавить элементы\n";
	a.push_back(11);
	a.push_back(21);
	a.push_front(1);
	a.print();
	std::cout << "По индексу\n";
	a.at(2);
	std::cout << "Удаление\n";
	a.pop_front();
	a.pop_back();
	a.print();
	std::cout << "Добавить элемент по индексу\n";
	a.push_back(11);
	a.push_back(21);
	a.push_front(1);
	a.insert(1, 10);
	a.print();
	return 0;
}