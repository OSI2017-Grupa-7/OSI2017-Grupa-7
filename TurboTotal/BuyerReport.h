#pragma once
#include "Date.h"
#include "Buyer.h"
#include "Article.h"
#include <fstream>
#include <vector>

void readForBuyerReport(std::string);


class BuyerReport//klasa za izvjestaj po kupcu koja sadrzi sve potrebna polja za izvjestaj 
{
	Date date;
	std::vector<Article> vec;
	double no_pdv, pdv, plus_pdv;
public:
	BuyerReport();
	void setDate(Date);
	~BuyerReport();
	void setNo_pdv(double);
	void setPdv(double);
	void setPlus_pdv(double);
	void setVec(std::vector<Article>);
	void print();
	Date getDate()const;
};

void printBuyerReport(std::vector<BuyerReport>);
void printArticleHeader();
void printArticleFooter();
void printAllArticlesForReport(std::vector<Article>);
Date findDate(std::string);

struct less_than_key
{
	inline bool operator() (const BuyerReport& struct1, const BuyerReport& struct2)
	{
		return (struct1.getDate() < struct2.getDate());
	}
};