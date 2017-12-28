#include "Racun.h"

Racun::Racun() {}

Racun::Racun(std::vector<Artikal> artikal, Kupac kupac,Datum datum): artikal(artikal),kupac(kupac),datum(datum){}

Racun::~Racun() {}

void Racun::setRacun(std::vector<Artikal> a, Kupac k, Datum d)
{
	artikal = a;
	kupac = k;
	datum = d;
}

void Racun::print()
{
	kupac.print();
	datum.print();
	for (unsigned int i = 0; i < artikal.size(); i++)
		artikal[i].print();
}
