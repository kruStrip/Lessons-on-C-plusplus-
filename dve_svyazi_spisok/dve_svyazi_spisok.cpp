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
	void push_front(int value) {
		Elements* newEl = new Elements(value);
		newEl->next = head;
		if (head == nullptr) {
			tail = newEl;
		}
		head = newEl;
		size++;
	}
};

int main()
{
    setlocale(LC_ALL, "");
}