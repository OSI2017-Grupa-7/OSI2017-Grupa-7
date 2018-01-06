#pragma once
#include <string>

typedef struct article
{
	char name[10], number[10]; 
	double total, price, amount;

}ARTICLE;

void readformat4(std::string& bill);