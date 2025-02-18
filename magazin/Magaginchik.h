#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>

class Magaginchik
{
	std::string name;
	std::map<std::string, std::string> clients;
	std::map<std::string, int> products;
	std::map<std::string, int> employees;
public:
	Magaginchik() {name = "Pyaterocka";}
	~Magaginchik() = default;
	
	void add_client(std::string client, std::string date) {
		clients.insert(std::pair<std::string, std::string>(client, date));
	}
	void list_clients() {
		std::cout << "Список клиентов:\n";
		for (auto& i : clients) {
			std::cout << "ФИО клиента: "<< i.first<< "\nДата покупки: "<< i.second;
			std::cout << "\n";
		}
	}
};

