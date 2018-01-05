#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

typedef struct article
{
	char name[10], number[10];
	double total, price, amount;

}ARTICLE;

void readformat4(std::string& bill)
{
	std::ifstream file(bill.c_str());
	std::string line;

	ARTICLE *array;
	std::string buyer, date;
	std::string trash;

	file >> trash >> buyer;
	getline(file, line);
	file >> trash >> date;
	date[2] = '.';
	date[5] = '.';

	FILE *f;
	int num = 0;
	if (f = fopen(bill.c_str(), "r"))
	{
		ARTICLE p;
		char pomo[50];
		for (int i = 0; i < 7; i++)
		{
			fgets(pomo, 50, f);
		}
		while (fscanf(f, "%s %s - %lf - %lf - %lf", p.name, p.number, &p.amount, &p.price, &p.total) == 5)
		{
			num++;
		}
		fclose(f);
	}

	array = (ARTICLE*)malloc((num + 1) * sizeof(ARTICLE));
	if (f = fopen(bill.c_str(), "r"))
	{
		char pomo[50];
		for (int i = 0; i < 7; i++)
		{
			fgets(pomo, 50, f);
		}
		int pom = 0;
		while (fscanf(f, "%s %s - %lf - %lf - %lf", array[pom].name, array[pom].number, &array[pom].amount, &array[pom].price, &array[pom].total) == 5)
		{
			pom++;
		}
		fclose(f);
	}

	std::string help;
	while (help != "Ukupno:")
	{
		file >> help;
	}

	double total, PDV, bezPDV;
	file >> bezPDV;
	getline(file, help);
	file >> trash >> PDV;
	getline(file, help);
	getline(file, help);
	file >> trash >> trash >> trash >> total;

	double sum = 0;
	for (int i = 0; i < num; i++)
		sum = sum + array[i].total;

	int brojac = 0;
	for (int i = 0; i < num; i++)
	{
		if ((array[i].price) * array[i].amount == array[i].total)
		{
			brojac++;
		}
	}

	double calcPDV;
	calcPDV = bezPDV * 17 / 100;

	if (bezPDV == sum && brojac == num && PDV == calcPDV)
	{
		//kupac.txt
		std::string buyer_dat;
		buyer_dat = "Kupci/" + buyer + ".txt";
		std::ofstream buyer_file(buyer_dat, std::ios::app);
		buyer_file << date << "." << std::endl;
		for (int i = 0; i < num; i++)
		{
			buyer_file << array[i].number << " " << array[i].name << " " << array[i].amount << " " << array[i].price << " " << array[i].total << std::endl;
		}
		bezPDV = total - PDV;
		buyer_file << bezPDV << std::endl;
		buyer_file << PDV << std::endl;
		buyer_file << total << std::endl;
		buyer_file << "------------------------------" << std::endl;
		//artikli
		for (int i = 0; i < num; i++)
		{
			std::string artikal = array[i].number;
			std::string article_dat;
			article_dat = "Artikli/" + artikal + ".txt";
			std::ofstream article_file(article_dat, std::ios::app);
			article_file << buyer << std::endl;
			article_file << date << "." << std::endl;
			article_file << array[i].amount << " " << array[i].price << " " << array[i].total << std::endl;
			article_file << "------------------------------" << std::endl;
		}

		//obradjeni_racuni
		std::ifstream old_file(bill);
		bill.erase(0, 7);
		std::ofstream processed_file("Obradjeni_racuni/" + bill);
		std::string line;
		while (getline(old_file, line))
		{
			processed_file << line << std::endl;
		}
	}
	else   //greska pri racunu
	{
		bill.erase(0, 7);
		std::string error_dat = "Error/" + bill.erase(bill.length() - 4, bill.length());
		error_dat += "_error.txt";
		std::ofstream proccesed_file(error_dat);
		proccesed_file << "Greska u obracunu ukupne cijene!" << std::endl;
	}

}