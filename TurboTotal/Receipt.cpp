#include "Receipt.h"
#include "Article.h"
#include "Buyer.h"
#include "Date.h"

Receipt::Receipt() {}

Receipt::Receipt(std::vector<Article> artikal, Buyer kupac, Date datum) : artikal(artikal), kupac(kupac), datum(datum) {}

Receipt::~Receipt() {}

void Receipt::setRacun(std::vector<Article> a, Buyer b, Date d)
{
	artikal = a;
	kupac = b;
	datum = d;
}

void Receipt::print()
{
	kupac.print();
	datum.print();
	for (unsigned int i = 0; i < artikal.size(); i++)
		artikal[i].print();
}
