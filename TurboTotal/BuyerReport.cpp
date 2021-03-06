#include "BuyerReport.h"
#include <sstream>
#include <algorithm>

void readForBuyerReport(std::string file_name)
{
	std::string name_file = "Kupci/" + file_name + ".txt";
	std::ifstream file(name_file);
	std::string line("0");
	std::string pom;
	std::vector<Article> v;
	std::vector<BuyerReport> vec;
	std::vector<Article> art_total;
	Article pom_art("a", "cedomir", 1);
	double totalForTotalReport = 0;
	art_total.push_back(pom_art);

	int buyer_report_counter = 0, k = 1;
	std::string counter;
	while (getline(file, counter))
	{
		if (counter[0] == '-')
			buyer_report_counter++;
	}//izbrojani buyer_reporti
	file.clear();
	file.seekg(0);
	if (file.is_open())
	{
		while (!file.eof() && buyer_report_counter)
		{
			buyer_report_counter--;
			v.erase(v.begin(), v.end());
			BuyerReport buyer_report;
			std::string end_of_bill;
			do
			{

				Article article;
				std::string date, code, name, amount, price, total;
				if (k == 1)
				{
					getline(file, date);//pronadjen datum jednog buyer_reporta	
					k = 0;
				}
				else
				{
					getline(file, date);
					getline(file, date);
				}
				Date d = findDate(date);
				end_of_bill = date;
				std::string articles, last_article;
				do
				{

					code.erase(); name.erase(); amount.erase(); price.erase(); total.erase();
					getline(file, articles);

					if (articles.length() < 10) { last_article = articles; break; };
					int i = 0, spaces = 0;
					for (int k = 0; k < articles.length(); k++)
						if (articles[k] == ' ')
							spaces++;//razlikovanje sifre: abc 123 i a123
					if (spaces == 4)
					{
						for (i; i < articles.length(); i++)
							if (articles[i] != ' ')
								code += articles[i];
							else break;
							i++;
							code += ' ';
							for (i; i < articles.length(); i++)
								if (articles[i] != ' ')
									code += articles[i];
								else break;
								i++;//pronalazak sifre artikla
					}
					else
					{
						for (i; i < articles.length(); i++)
							if (articles[i] != ' ')
								code += articles[i];
							else break;
							i++;
					}
					for (i; i < articles.length(); i++)
						if (articles[i] != ' ')
							amount += articles[i];
						else break;//kolicina artikla
						i++;
						for (i; i < articles.length(); i++)
							if (articles[i] != ' ')
								price += articles[i];
							else break;//cijena artikla

							i++;
							for (i; i < articles.length(); i++)
								if (articles[i] != ' ')
									total += articles[i];
								else break;//ukupna cijena artikla


								article.setCode(code);
								//article.setName(name);
								article.setAmount(stod(amount));
								article.setPrice(stod(price));
								article.setTotal(stod(total));
								totalForTotalReport += stod(total);//dodavanje za ukupnu cijenu
								v.push_back(article);//dodan jedan artikal u vektor artikal
								int p = 1;
								for (unsigned int i = 0; i < art_total.size(); i++)
									if (article.getCode() == art_total[i].getCode())
									{
										art_total[i].setAmount(article.getAmount() + art_total[i].getAmount());
										art_total[i].setTotal(article.getTotal() + art_total[i].getTotal());
										p = 0;
										break;
									}
								if (p == 1)
								{
									art_total.push_back(article);
								}//dodavanje artikala u vektor za konacan izvjestaj svih artiklaa za jednog kupca, ako vec ima artikal, samo poveca total i kolicinu

				} while (articles.length() > 8);

				std::string pdvs;

				////////////////////////////////
				std::string no_pdv = last_article;
				std::string pom_line;
				std::string pdv;
				std::string plus_pdv;
				file >> pdv;
				file >> plus_pdv;
				file >> pom_line;

				buyer_report.setNo_pdv(stod(no_pdv));
				buyer_report.setPdv(stod(pdv));
				buyer_report.setPlus_pdv(stod(plus_pdv));//pronadjene, setovane velicine bez pdv, pdv, sa pdv

				buyer_report.setDate(d);//setovan datum jednom buyer_reportu
				buyer_report.setVec(v);//setovan vektor artikala u jednom buyer_reportu
				vec.push_back(buyer_report);//dodan jedan buyer_report u vektor


				end_of_bill = pom_line;
			} while (end_of_bill[0] != '-');
		}
		sort(vec);
		printBuyerReport(vec);
		art_total.erase(art_total.begin());
		std::cout << std::endl << "UKUPNO ZA SVE ARTIKLE: " << std::endl;
		printAllArticlesForReport(art_total);

		std::ifstream fileee("Valuta.txt");
		std::string value;
		fileee >> value;//citanje valute

		std::ostringstream os;
		os << totalForTotalReport;
		std::string totalForTotalReport_value = os.str() + ' ' + value;//stvaranje formata oblika 'cijena (valuta)'

		double pdv = totalForTotalReport * 0.17;

		std::ostringstream oss;
		oss << pdv;
		std::string pdv_value = oss.str() + ' ' + value;

		double plus_pdv = pdv + totalForTotalReport;
		std::ostringstream osss;
		osss << plus_pdv;
		std::string plus_pdv_value = osss.str() + ' ' + value;

		std::cout << std::endl << "Bez PDV: " << totalForTotalReport_value << std::endl;
		std::cout << "PDV: " << pdv_value << std::endl;
		std::cout << "Sa PDV: " << plus_pdv_value << std::endl;//ispis ukupnog pdva i sve sto ide uz njega
	}

	else
	{
		std::cout << std::endl << "Ne postoji kupac sa tim imenom!!" << std::endl;
	}


	getchar();
	getchar();
}

void printBuyerReport(std::vector<BuyerReport> vec)
{
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		vec[i].print();
	}
}

void printArticleHeader()
{
	std::cout << std::endl << "======================================" << std::endl;
	std::cout << "SIFRA     KOLICINA  CIJENA    UKUPNO" << std::endl;
	std::cout << "======================================" << std::endl;
}

void printArticleFooter()
{
	std::cout << "======================================" << std::endl;
}

void printAllArticlesForReport(std::vector<Article> vec)
{
	printArticleHeader();
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		vec[i].printForReport();
	}
	printArticleFooter();
}

Date findDate(std::string date)
{
	Date d;
	int i;
	std::string day, month, year;
	for (i = 0; i < date.length(); i++)
		if (date[i] != '.')
			day += date[i];
		else break;
		d.setDay(stoi(day));
		i++;
		for (i; i < date.length(); i++)
			if (date[i] != '.')
				month += date[i];
			else break;
			d.setMonth(stoi(month));
			i++;
			for (i; i < date.length(); i++)
				if (date[i] != '.')
					year += date[i];
				else break;
				d.setYear(stoi(year));

				return d;
}

void sort(std::vector<BuyerReport>& vec)
{
	unsigned int i, j;
	for (i = 0; i < vec.size() - 1; i++)
		for (j = 0; j < vec.size() - i - 1; j++)
			if (!(vec[j].getDate() < vec[j + 1].getDate()))
			{
				BuyerReport a = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = a;
			}
}

BuyerReport::BuyerReport() {}

void BuyerReport::setDate(Date d)
{
	date = d;
}

BuyerReport::~BuyerReport() {}

void BuyerReport::setNo_pdv(double d) { no_pdv = d; }

void BuyerReport::setPdv(double d) { pdv = d; }

void BuyerReport::setPlus_pdv(double d) { plus_pdv = d; }

void BuyerReport::setVec(std::vector<Article> v) { vec = v; }

void BuyerReport::print()
{
	std::cout << std::endl << "Datum: ";
	date.print(); std::cout << std::endl;
	printArticleHeader();
	for (unsigned int i = 0; i < vec.size(); i++)
		vec[i].printForReport();

	std::ifstream file("Valuta.txt");
	std::string value;
	file >> value;

	std::ostringstream os;
	os << no_pdv;
	std::string no_pdv_value = os.str() + ' ' + value;

	std::ostringstream oss;
	oss << pdv;
	std::string pdv_value = oss.str() + ' ' + value;

	std::ostringstream osss;
	osss << plus_pdv;
	std::string plus_pdv_value = osss.str() + ' ' + value;

	std::cout << std::endl << "Bez PDV: " << no_pdv_value << std::endl;
	std::cout << "PDV: " << pdv_value << std::endl;
	std::cout << "Sa PDV: " << plus_pdv_value << std::endl;
	printArticleFooter();
}

Date BuyerReport::getDate()const
{
	return date;
}

bool BuyerReport::operator<(BuyerReport b)
{
	if (date < b.getDate())return true;
	else return false;
}
