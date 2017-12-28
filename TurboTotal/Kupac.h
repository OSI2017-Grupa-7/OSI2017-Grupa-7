#pragma once
#include <string>
#include <iostream>
class Kupac
{
	std::string ime, prezime;
public:
	Kupac();
	Kupac(std::string, std::string);
	~Kupac();
	void setIme(std::string);
	void setPrezime(std::string);
	std::string getIme();
	std::string getPrezime();
	void print();
};

