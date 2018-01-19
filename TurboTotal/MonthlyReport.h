#pragma once
#include <iostream>
#include "Logo.h"
#include <vector>
#include <string>
#include <fstream>
using std::string;

struct MonthlyDate//struktura za datum
{
	string day, month, name;
};

struct MonthlyArticle//posebna struktura koja oznacava artikal koji sluzi za mjesecni izvjestaj
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

void Monthly(int, int);//funkcija koja vrsi dohvatanje podataka iz datoteka za artikle
void ReportOutput(std::vector<MonthlyArticle>);//funkcija za ispis artikala na standardni izlaz
bool checkDate(string, int, int);//funkcija koja provjerava da li je datum koji se nalazi u datoteci u opsegu koji nama treba(tj. da li se datum nalazi u unesenom mjesecu)

