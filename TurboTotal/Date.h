#pragma once
#include <iostream>

class Date
{
	int dan, mjesec, godina;
public:
	Date();
	Date(int, int, int);
	void setDatum(int, int, int);
	void print();
	~Date();
};

