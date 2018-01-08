#pragma once
#include <iostream>
#include <string>
class Article
{
	std::string name, code;
	double price, amount;
	
public:
	Article();
	Article(std::string,std::string, double);
	~Article();
	void setName(std::string);
	void setCode(std::string);
	void setPrice(double);
	void setAmount(double);
	std::string getName();
	std::string getCode();
	double getPrice();
	double getAmount() { return amount; }
    void print();
};

