#pragma once
#include "Buyer.h"
#include "Article.h"
#include "Date.h"
#include <vector>
class Receipt
{
	std::vector<Article> artikal;
	Buyer kupac;
	Date datum;
public:
	Receipt();
	Receipt(std::vector<Article>, Buyer, Date);
	~Receipt();
	void setRacun(std::vector<Article>, Buyer, Date);
	void print();
};

