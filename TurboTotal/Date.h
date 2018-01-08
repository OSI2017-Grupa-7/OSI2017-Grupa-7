#pragma once
#include <iostream>

class Date
{
	int day, month, year;
public:
	Date();
	Date(int, int, int);
	void setDate(int, int, int);
	void print();
	~Date();
};

