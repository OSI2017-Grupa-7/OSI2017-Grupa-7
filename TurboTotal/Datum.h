#pragma once
#include <iostream>

class Datum
{
	int dan, mjesec, godina;
public:
	Datum();
	Datum(int, int, int);
	void setDatum(int, int, int);
	void print();
	~Datum();
};

