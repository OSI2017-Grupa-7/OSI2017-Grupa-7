#pragma once
#include "Date.h"
#include "Buyer.h"
#include "Article.h"
#include <fstream>
#include <vector>

namespace date {
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
		bool operator<(BuyerReport);
	};

	void printArticleHeader();
	void printArticleFooter();
	void printAllArticlesForReport(std::vector<Article>);//ispisuje sve artikle koje je kupio jedan kupac
	Date findDate(std::string);//od stringa datuma vraca objekat klase Datum
	void sort(std::vector<BuyerReport>&);
	void parseDateDot(const std::string&, int&, int&, int&); //izdvaja iz stringa posebne varijable za dan, mjesec i godinu
	int dateCheck(std::string, std::string, Date&); // provjerava da li je odredjeni datum u zadatom opsegu
	void printBuyerReport(std::string, std::string, std::vector<BuyerReport>);
}