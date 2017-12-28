#pragma once
#include <iostream>
#include <string>
class Article
{
	std::string naziv, sifra;
	double cijena;
	
public:
	Article();
	Article(std::string,std::string sifra, double);
	~Article();
	void setNaziv(std::string);
	void setSifra(std::string);
	void setCijena(double);
	std::string getNaziv();
	std::string getSifra();
	double getCijena();
    void print();
};

