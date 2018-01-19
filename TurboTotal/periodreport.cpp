#include "periodreport.h"
#include <stdlib.h>
#include <string>
#include <sstream>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <Windows.h>
#include <iomanip>
#include "Logo.h"
#include "Report.h"


int parseDate(const std::string &input) //konverzija datuma iz stringa u cjelobrojni tip
{
	int month;
	int day;
	int year;
	if (std::sscanf(input.c_str(), "%d.%d.%d.", &day, &month, &year) != 3) {
		return 0;
	}
	else {
		return 10000 * year + 100 * month + day;
	}
}

bool isLeap(int year)  // provjera da li je godina prestupna
{
	return (((year % 4 == 0) && (year % 100 != 0)) ||
		(year % 400 == 0));
}

const int MAX_VALID_YR = 9999;
const int MIN_VALID_YR = 1800;

int checkDate(std::string &date)  //provjera validnosti datuma
{
	int d, m, y;
	sscanf(date.c_str(), "%d.%d.%d", &d, &m, &y);

	if (y > MAX_VALID_YR || y < MIN_VALID_YR)
		return false;
	if (m < 1 || m > 12)
		return false;
	if (d < 1 || d > 31)
		return false;

	if (m == 2)
	{
		if (isLeap(y))
			return (d <= 29);
		else
			return (d <= 28);
	}

	if (m == 4 || m == 6 || m == 9 || m == 11)
		return (d <= 30);

	return true;
}
std::string to_string_with_precision(const double a_value, const int n = 2)
{
	std::ostringstream out;
	out << std::setprecision(n) << a_value;
	return out.str();
}


void articleReport(std::string& bill, int date1, int date2)
{
	std::string path = "Artikli/" + bill + ".txt";
	std::ifstream file(path.c_str());
	
	std::string buyer, datestr, line, pom;

	std::fstream f(bill);
	int pomo = 0, counter = 0, count = 0;
	while (getline(file,pom))
	{
		pomo = file.tellg();
	}
	file.clear();
	file.seekg(0);
	while (counter != pomo) // prebrojavanje artikala
	{
		getline(file, buyer);
		getline(file, datestr);
		file.clear();
		file.seekg(counter);
		int date = parseDate(datestr);
		if (date1 <= date && date <= date2)
		{
			count++;
		}
		getline(file, pom);
		getline(file, pom);
		counter = file.tellg();
	}

	BUY *a = (BUY*)malloc((count) * sizeof(BUY));
	counter = 0;
	file.clear();
	file.seekg(0);
	int i = 0;
	
	while(counter != pomo)  // citanje artikala u niz
	{
		getline(file, buyer);
		getline(file, datestr);
		file.clear();
		file.seekg(counter);
		int date = parseDate(datestr);
		
		if (date1 <= date && date <= date2)
		{
			getline(file, buyer);
			sscanf(buyer.c_str(), "%s", a[i].buyer);
			getline(file, datestr);
			sscanf(datestr.c_str(), "%s", a[i].date);
			getline(file, pom);
			sscanf(pom.c_str(), "%d %lf %lf", &a[i].amount, &a[i].price, &a[i].total);
			getline(file, pom);
			i++;
		}
		else
		{
			getline(file, pom);
			getline(file, pom);
			getline(file, pom);
			getline(file, pom);
		}
		counter = file.tellg();
	}

	for (int i = 0; i < count - 1; i++) // sortiranje niza artikala po datumima
	{
		for (int j = 0; j < count - 1 - i; j++)
		{
			int comp1 = parseDate(a[j].date);
			int comp2 = parseDate(a[j + 1].date);
			if (comp1 > comp2)
			{
				BUY pom = a[j];
				a[j] = a[j + 1];
				a[j + 1] = pom;
			}
		}
	}
	std::ifstream currency("Valuta.txt"); //dohvatanje valute iz txt fajla
	std::string value;
	currency >> value;
	
	double total = 0;
	int amount = 0;
	
	// ispis na standardni izlaz
	std::cout << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < count; i++)
	{
		total += a[i].total; amount += a[i].amount;
		std::cout << "Datum: " << a[i].date << std::endl;
		std::cout << "Kupac: " << a[i].buyer << std::endl;
		std::cout << std::endl;
		std::string price = to_string_with_precision(a[i].price, 4) + " " + value;
		std::string total = to_string_with_precision(a[i].total, 4) + " " + value;
		std::cout << "==================================" << std::endl;
		std::cout << "  " << "KOLICINA" << "     " << "CIJENA" << "     " << "UKUPNO" << std::endl;
		std::cout << "==================================" << std::endl;
		std::cout << "  " << std::setw(13) << std::left  << a[i].amount << std::setw(11) << std::left << price  << total << std::endl;
		std::cout << "==================================" << std::endl;
		std::cout << std::endl;
	}

	double PDV = total * 17 / 100;
	double wPDV = total - PDV;

	std::string PDVS = to_string_with_precision(PDV, 10) + " " + value;
	std::string wPDVS = to_string_with_precision(wPDV, 10) + " " + value;
	std::string totalS = to_string_with_precision(total, 10) + " " + value;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "KONACNO: " << std::endl;
	std::cout << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << "  " << "KOLICINA" << "     " << "UKUPNO BEZ PDV" << "     " << "PDV" << "           " << "UKUPNO" << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << "  " << std::left << std::setw(13) << amount << std::left << std::setw(19) << wPDVS << std::left << std::setw(14) << PDVS << std::left << std::setw(2) << totalS << std::endl;
}