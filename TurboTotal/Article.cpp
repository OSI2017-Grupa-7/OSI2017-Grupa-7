#include "Article.h"

Article::Article(){}

Article::Article(std::string naziv, std::string sifra, double cijena) :naziv(naziv), sifra(sifra), cijena(cijena) {}

Article::~Article(){}

void Article::setNaziv(std::string n) { naziv = n; }

void Article::setSifra(std::string s) { sifra = s; }

void Article::setCijena(double c) { cijena = c; }

void Article::setKolicina(double kol)
{
	kolicina = kol;
}

std::string Article::getNaziv() { return naziv;}

std::string Article::getSifra() { return sifra;}

double Article::getCijena() { return cijena;}

void Article::print() { std::cout << sifra << " " << naziv<<" " << cijena<<std::endl;}


