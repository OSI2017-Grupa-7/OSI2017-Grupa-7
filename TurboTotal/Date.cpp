#include "Date.h"

Date::Date(){}

Date::Date(int dan, int mjesec, int godina):dan(dan),mjesec(mjesec),godina(godina){}

void Date::setDatum(int d, int m, int g)
{
	dan = d;
	mjesec = m;
	godina = g;
}

void Date::print() { std::cout << dan << "." << mjesec << "." << godina<<"."<<std::endl;}

Date::~Date() {}
