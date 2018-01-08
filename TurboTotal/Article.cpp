#include "Article.h"

Article::Article(){}

Article::Article(std::string name, std::string code, double price) :name(name), code(code), price(price) {}

Article::~Article(){}

void Article::setName(std::string n) { name = n; }

void Article::setCode(std::string s) { code = s; }

void Article::setPrice(double c) { price = c; }

void Article::setAmount(double amountt) { amount = amountt;}

std::string Article::getName() { return name;}

std::string Article::getCode() { return code;}

double Article::getPrice() { return price;}

void Article::print() { std::cout << code << " " << name<<" " <<price<<std::endl;}


