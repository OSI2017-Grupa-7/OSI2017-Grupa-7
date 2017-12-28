#pragma once
#include <string>
#include <iostream>
class Buyer
{
	std::string ime, prezime;
public:
	Buyer();
	Buyer(std::string, std::string);
	~Buyer();
	void setIme(std::string);
	void setPrezime(std::string);
	std::string getIme();
	std::string getPrezime();
	void print();
};

