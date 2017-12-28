#include "Buyer.h"

Kupac::Kupac(){}

Kupac::Kupac(std::string ime, std::string prezime):ime(ime),prezime(prezime){}

Kupac::~Kupac(){}

void Kupac::setIme(std::string i) { ime = i; }

void Kupac::setPrezime(std::string p) { prezime = p; }

std::string Kupac::getIme() { return ime;}

std::string Kupac::getPrezime() { return prezime; }

void Kupac::print() { std::cout << ime << " " << prezime<<std::endl;}
