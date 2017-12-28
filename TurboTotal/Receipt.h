#pragma once
#include "Kupac.h"
#include "Artikal.h"
#include "Datum.h"
#include <vector>
class Receipt
{
	std::vector<Artikal> artikal;
	Buyer kupac;
	Date datum;
public:
	Receipt();
	Receipt(std::vector<Article> , Buyer,Date);
	~Receipt();
	void setRacun(std::vector<Article>, Buyer,Date);
	void print();
};

