#pragma once
#include "Kupac.h"
#include "Artikal.h"
#include "Datum.h"
#include <vector>
class Racun
{
	std::vector<Artikal> artikal;
	Kupac kupac;
	Datum datum;
public:
	Racun();
	Racun(std::vector<Artikal> , Kupac,Datum);
	~Racun();
	void setRacun(std::vector<Artikal>, Kupac,Datum);
	void print();
};

