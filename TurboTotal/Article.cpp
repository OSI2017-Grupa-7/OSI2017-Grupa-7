#include "Article.h"
#include <fstream>
#include <sstream>


Article::Article(){}

Article::Article(std::string name, std::string code, double price) :name(name), code(code), price(price) {}

Article::~Article() {}

void Article::setName(std::string n) { name = n; }

void Article::setCode(std::string s) { code = s; }

void Article::setPrice(double c) { price = c; }

void Article::setAmount(double amountt) { amount = amountt;}

void Article::setTotal(double t) { total = t;}

std::string Article::getName() { return name;}

std::string Article::getCode() { return code;}

double Article::getPrice() { return price;}

void Article::print() { std::cout << std::setw(10)<<std::left<< code << std::setw(10)<<std::left<<amount<< std::setw(10) <<std::left<< price<<std::setw(7) <<std::left<< total << std::endl; }

void Article::printForReport()
{
	std::ifstream file("Valuta.txt");
	std::string value;
	file >> value;
	
	std::ostringstream os;
	os << price;
	std::string price_value = os.str()+ ' ' + value;
	std::ostringstream oss;
	oss << total;
	std::string total_value = oss.str() +' '+ value;

	std::cout << std::setw(10) << std::left << code << std::setw(10) << std::left << amount << std::setw(10) << std::left << price_value<< std::setw(7) << std::left << total_value<< std::endl;
}


