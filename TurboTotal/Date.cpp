#include "Date.h"

Date::Date(){}

Date::Date(int day, int month, int year):day(day),month(month),year(year){}

void Date::setDate(int d, int m, int g)
{
	day = d;
	month = m;
	year = g;
}

void Date::print() { std::cout << day << "." << month << "." << year<<"."<<std::endl;}

Date::~Date() {}
