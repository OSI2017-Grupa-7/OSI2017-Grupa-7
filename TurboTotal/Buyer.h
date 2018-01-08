#pragma once
#include <string>
#include <iostream>
class Buyer
{
	std::string name, surname;
public:
	Buyer();
	Buyer(std::string, std::string);
	~Buyer();
	void setName(std::string);
	void setSurname(std::string);
	std::string getName();
	std::string getSurname();
	void print();
};

