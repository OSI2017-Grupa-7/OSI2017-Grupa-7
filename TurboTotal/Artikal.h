#pragma once
#include <iostream>
#include <string>
class Artikal
{
	std::string naziv, sifra;
	double cijena;
	
public:
	Artikal();
	Artikal(std::string,std::string sifra, double);
	~Artikal();
	void setNaziv(std::string);
	void setSifra(std::string);
	void setCijena(double);
	std::string getNaziv();
	std::string getSifra();
	double getCijena();
    void print();
};

