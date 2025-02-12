#pragma once
#include <iostream>

#ifndef ANIMAL_H
#define ANIMAL_H


class Animal
{
protected:
	unsigned age;
public:
	Animal(unsigned age = 2) : age(age) {};
	Animal(Animal const& other) : age(other.age) {};
	virtual~Animal() = default;

	virtual void say() = 0;
};

class Cat : virtual public Animal {
protected:
	std::string name;
public:
	Cat(std::string const& name = "Barsik") : Animal(), name(name) {}
	Cat(Cat const& other) : Animal(), name(other.name) {}
	~Cat() {
		std::cout << name << "life";
	}

	std::string getName() const {
		return name;
	}
	void setName(std::string const& name) {
		this->name = name;
	}
	void say() override {
		std::cout << "Meow";
	}
};

class Dog : virtual public Animal {
protected:
	std::string type;
public:
	Dog(std::string const& name = " Haski ") : Animal(), type(name) {};
	Dog(Dog const& other) : Animal(), type(other.type) {};
	~Dog() {
		std::cout << type << " life ";
	}

	std::string getName() const {
		return type;
	}
	void setName(std::string const& name) {
		this->type = name;
	}
	void say() override {
		std::cout << " Gauph ";
	}
};

class Catdog : public Cat, public Dog {
protected:
	public:
		Catdog(std::string const& type = "Terier", std::string const& name = "Ryzhyk")
			: Cat(name)
			, Dog(type)
		{}
		Catdog(Catdog const& other)
			: Cat(other.name)
			, Dog(other.type)
		{}
		~Catdog() {
			std::cout << "Oh, no!\n";
		}
		void say() override {
			std::cout << "Meowoof!" << std::endl;
		}
};


#endif //ANIMAL_H
