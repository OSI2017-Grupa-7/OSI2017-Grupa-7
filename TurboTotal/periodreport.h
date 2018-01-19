#pragma once
#include <string>
#include <conio.h>
#include <Windows.h>

typedef struct buy
{
	char buyer[100];
	char date[12];
	int amount;
	double price, total;

}BUY;

int parseDate(const std::string &input);

void articleReport(std::string& s, int date1, int date2);

int checkDate(std::string &date);

std::string input();