#pragma once
#include <iostream>

class Date
{
	int day, month, year;
public:
	Date();
	Date(int, int, int);
	void setDate(int, int, int);
	int getDay();
	int getMonth();
	int getYear();
	void setDay(int);
	void setMonth(int);
	void setYear(int);
	void print();
	bool operator<(Date);
	~Date();
};

