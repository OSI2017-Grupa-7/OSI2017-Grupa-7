#pragma once
#include <iostream>
#include <string>
#include <iomanip>
class Article
{
	std::string name, code;
	double price, amount,total;
	
public:
	Article();
	Article(std::string,std::string, double);
	~Article();
	void setName(std::string);
	void setCode(std::string);
	void setPrice(double);
	void setAmount(double);
	void setTotal(double);
	std::string getName();
	std::string getCode();
	double getPrice();
	double getAmount() { return amount; }
    void print();
	void printForReport();
};

