#include "Buyer.h"

Buyer::Buyer(){}

Buyer::Buyer(std::string ime, std::string prezime):ime(ime),prezime(prezime){}

Buyer::~Buyer(){}

void Buyer::setIme(std::string i) { ime = i; }

void Buyer::setPrezime(std::string p) { prezime = p; }

std::string Buyer::getIme() { return ime;}

std::string Buyer::getPrezime() { return prezime; }

void Buyer::print() { std::cout << ime << " " << prezime<<std::endl;}
