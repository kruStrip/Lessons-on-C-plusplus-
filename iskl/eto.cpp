#include "eto.h"
#include <list>
#include <iterator>
#include <iostream>
int main() {
    setlocale(0, "");
	Tree<int> t;
    t.add(1);
    t.add(5);
    t.add(0);
    t.add(7);
    t.add(8);
    t.add(-2);
    t.add(3);
    t.add(-1);
    std::cout << "Все значенгия множества: \n";
    /*t.print();*/

    /*for (int const& it : t) {
        std::cout << it << " ";
    }*/

	for (Tree<int>::iterator it = t.begin(); it != t.end(); ++it) {
		std::cout << *it << "\n";
	}

	return 0;
}
