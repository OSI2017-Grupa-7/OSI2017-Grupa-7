#include "Artikal.h"

Artikal::Artikal(){}

Artikal::Artikal(std::string naziv, std::string sifra, double cijena) :naziv(naziv), sifra(sifra), cijena(cijena) {}

Artikal::~Artikal(){}

void Artikal::setNaziv(std::string n) { naziv = n; }

void Artikal::setSifra(std::string s) { sifra = s; }

void Artikal::setCijena(double c) { cijena = c; }

std::string Artikal::getNaziv() { return naziv;}

std::string Artikal::getSifra() { return sifra;}

double Artikal::getCijena() { return cijena;}

void Artikal::print() { std::cout << sifra << " " << naziv<<" " << cijena<<std::endl;}


