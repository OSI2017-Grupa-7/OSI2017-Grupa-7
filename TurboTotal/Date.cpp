#include "Date.h"

Date::Date() {}

Date::Date(int day, int month, int year) :day(day), month(month), year(year) {}

void Date::setDate(int d, int m, int g)
{
	day = d;
	month = m;
	year = g;
}

int Date::getDay()
{
	return day;
}

int Date::getMonth()
{
	return month;
}

int Date::getYear()
{
	return year;
}

void Date::setDay(int d)
{
	day = d;
}

void Date::setMonth(int m)
{
	month = m;
}

void Date::setYear(int y)
{
	year = y;
}

void Date::print() { std::cout << day << "." << month << "." << year << "." << std::endl; }

bool Date::operator<(Date d)
{
	if (year > d.year)return false;
	if ((year == d.year) && month > d.month)return false;
	if ((year == d.year) && (month == d.month) && day > d.day)return false;
	return true;
}

Date::~Date() {}
