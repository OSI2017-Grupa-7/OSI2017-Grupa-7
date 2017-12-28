#include "Date.h"

Datum::Datum(){}

Datum::Datum(int dan, int mjesec, int godina):dan(dan),mjesec(mjesec),godina(godina){}

void Datum::setDatum(int d, int m, int g)
{
	dan = d;
	mjesec = m;
	godina = g;
}

void Datum::print() { std::cout << dan << "." << mjesec << "." << godina<<"."<<std::endl;}

Datum::~Datum() {}
