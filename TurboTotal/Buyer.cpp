#include "Buyer.h"

Buyer::Buyer() {}

Buyer::Buyer(std::string name, std::string surname) :name(name), surname(surname) {}

Buyer::~Buyer() {}

void Buyer::setName(std::string i) { name = i; }

void Buyer::setSurname(std::string p) { surname = p; }

std::string Buyer::getName() { return name; }

std::string Buyer::getSurname() { return surname; }

void Buyer::print() { std::cout << name << " " << surname << std::endl; }
