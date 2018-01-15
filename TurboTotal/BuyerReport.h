#pragma once
#include "Date.h"
#include "Buyer.h"
#include "Article.h"
#include <fstream>
#include <vector>

void readForBuyerReport(std::string);


class BuyerReport//klasa za izvjestaj po kupcu koja sadrzi sve potrebna polja za izvjestaj 
{
	std::string date;
	std::vector<Article> vec;
	double no_pdv, pdv, plus_pdv;
public:
	BuyerReport();
	void setDate(std::string);
	~BuyerReport();
	void setNo_pdv(double);
	void setPdv(double);
	void setPlus_pdv(double);
	void setVec(std::vector<Article>);
	void print();
};

void printBuyerReport(std::vector<BuyerReport>);
void printArticleHeader();
void printArticleFooter();
void printAllArticlesForReport(std::vector<Article>);