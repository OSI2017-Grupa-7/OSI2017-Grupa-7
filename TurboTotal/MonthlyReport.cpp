#include "MonthlyReport.h"
#include "BillsReader.h"
#include <cctype>
#include <algorithm>
#include <iomanip>

bool checkDate(string date, int month, int year)
{
	string monthS, yearS, dayS;
	int monthI, yearI;
	int i = 0;
	std::replace(date.begin(), date.end(), '.', ' ');//funkcija koja zamjenjuje . u datumu sa praznim prostorom
	while (date[i] != ' ')//hvatanje dana u datumu
	{
		dayS += date[i];
		i++;
	}
	i++;
	while (date[i] != ' ')//hvatanje mjeseca u datumu
	{
		monthS += date[i];
		i++;
	}
	i++;
	while (date[i])//hvatanje godine u mjesecu
	{
		yearS += date[i];
		i++;
	}



	monthI = stoi(monthS);//funkcija koja vrsi pretvaranje stringa u integer
	yearI = stoi(yearS);

	if (yearI == year && monthI == month) return true;
	else return false;
}

void ReportOutput(std::vector<MonthlyArticle> vec)
{

	std::cout << std::endl;
	std::cout << std::endl;
	double sum = 0;
	string currency;
	std::ifstream currency_file("Valuta.txt");//hvatanje valute iz datoteke "Valuta.txt"
	currency_file >> currency;
	currency_file.close();


	std::cout << "======================================================================================\n";
	std::cout << "SIFRA          KUPAC               DATUM             KOLICINA   CIJENA     UKUPNO\n";
	std::cout << "======================================================================================\n";
	for (int i = 0; i < vec.size(); i++)
	{
		double total, quant, price;
		quant = stod(vec[i].quant); price = stod(vec[i].price);
		total = quant*price;
		sum += total;



		std::cout << std::left << std::setw(15) << vec[i].code << std::left << std::setw(20) << vec[i].buyer << std::left << std::setw(18) << vec[i].date << std::left << std::setw(11) << vec[i].quant << std::left << std::setw(5) << vec[i].price + ' ' + currency << "     " << total << " " << currency << std::endl;
	}
	std::cout << std::endl;
	double pdv, total_pdv;
	pdv = 17 * sum / 100;
	total_pdv = sum + pdv;
	std::cout << "Bez PDV: " << sum << " " << currency << std::endl;
	std::cout << "PDV: " << pdv << " " << currency << std::endl;
	std::cout << "Sa PDV: " << total_pdv << " " << currency << std::endl;
	std::cout << "======================================================================================\n";
}


void Monthly(int month, int year)
{
	std::vector<std::string> articles = get_filenames("Artikli");//smijestanje imena fajlova iz foldera "Artikli" u neki niz stringova
	for (int i = 0; i < articles.size(); i++)
	{
		articles[i].erase(0, 8);//brisanje prvih 8 karaktera u nazivu datoteke


	}
	std::vector<string>articlenames = articles;
	for (int i = 0; i < articles.size(); i++)
	{
		articlenames[i].erase(articlenames[i].length() - 4, articlenames[i].length());//brisanje .txt iz imena datoteke


	}
	std::vector<MonthlyArticle> vectorArt;
	MonthlyArticle pomart;
	string pomstr;
	int num = 0;

	while (num < articles.size())
	{
		std::ifstream fp("Artikli/" + articles[num]);
		while (!fp.eof())//"setanje" po datoteci i pribavljanje potrebnih podataka za ispis
		{
			pomart.code = articlenames[num];

			std::getline(fp, pomart.buyer);
			std::getline(fp, pomart.date);
			fp >> pomart.price;
			fp >> pomart.quant;
			fp >> pomart.total;
			std::getline(fp, pomstr);
			std::getline(fp, pomstr);
			if (fp.eof())break;//break ukoliko dodje do kraja fajla,jer se eof() razlikuje od datoteke do datoteke
			if (checkDate(pomart.date, month, year))
				vectorArt.push_back(pomart);


		}
		num++;
	}



	std::sort(vectorArt.begin(), vectorArt.end());//sortiranje artikala po datumima


	ReportOutput(vectorArt);

}


