#pragma once
#include <iostream>
#include "Logo.h"
#include <vector>
#include <string>
#include <fstream>
using std::string;

struct MonthlyDate
{
	string day, month, name;
};

struct MonthlyArticle
{
	string code, price, quant, total, buyer;
	string date;
	bool operator<(MonthlyArticle& a)
	{
		string dayS, daySa;
		int i = 0, j = 0, dayI, dayIa;
		while (date[i] != '.')
		{
			dayS += date[i];
			i++;
		}

		while (a.date[j] != '.')
		{
			daySa += a.date[j];
			j++;
		}

		dayI = stoi(dayS);
		dayIa = stoi(daySa);

		return dayI < dayIa;
	}
};

void Monthly(int, int);
void ReportOutput(std::vector<MonthlyArticle>);
bool checkDate(string, int, int);

