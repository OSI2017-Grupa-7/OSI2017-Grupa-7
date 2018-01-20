#include "Report.h"
#include  "Logo.h"
#include "BuyerReport.h"
#include "MonthlyReport.h"
#include "periodreport.h"
#include "ArticleReport.h"
#include "BuyerDateReport.h"

void buyerReport()
{
	char option4;
	do
	{
		system("cls");
		logoS(); std::cout << std::endl << "ODABRALI STE OPCIJU PREGLED PODATAKA ZA ODREDJENOG KUPCA" << std::endl << std::endl;
		std::cout << std::endl << "1. Ukupni pregled podataka za odredjenog kupca" << std::endl;
		std::cout << "2. Pregled podataka za odredjenog kupca u trazenom vremenskom intervalu" << std::endl;
		std::cout << std::endl << "Odaberi opciju: "; std::cin >> option4;
	} while (option4 != '1' && option4 != '2');
	if (option4 == '1')
	{
		system("cls");
		logoS();
		std::cout << std::endl << "IZVJESTAJ PO KUPCU" << std::endl << std::endl;
		std::cout << std::endl << "Unesite kupca: ";
		std::string name = input();

		system("cls");
		logoS();
		std::cout << std::endl << "IZVJESTAJ ZA KUPCA" << std::endl;
		std::cout << std::endl << "Kupac: " << name << std::endl;

		readForBuyerReport(name);
	}
	if (option4 == '2')
	{
		system("cls");
		logoS();
		std::cout << std::endl << "IZVJESTAJ PO KUPCU" << std::endl << std::endl;
		std::cout << std::endl << "Unesite kupca: ";
		std::string name = input();

		system("cls");
		logoS();
		std::cout << std::endl << "IZVJESTAJ ZA KUPCA" << std::endl;
		std::cout << std::endl << "Kupac: " << name << std::endl;

		readForBuyerDateReport(name);
	}
}

void productReport()
{
	char option4;
	do
	{
		system("cls");
		logoS(); std::cout << std::endl << "ODABRALI STE OPCIJU PREGLED PODATAKA ZA ODREDJENI PROIZVOD" << std::endl << std::endl;
		std::cout << std::endl << "1. Ukupni pregled podataka za odredjeni proizvod" << std::endl;
		std::cout << "2. Pregled podataka za odredjeni proizvod u vremenskom intervalu" << std::endl;
		std::cout << std::endl << "Odaberi opciju: "; std::cin >> option4;
	} while (option4 != '1' && option4 != '2');
	if (option4 == '1')
	{
		system("cls");
		logoS();
		std::cout << std::endl << "UKUPNI IZVJESTAJ PO ARTIKLU" << std::endl << std::endl;
		std::string sifra;
		std::cout << "Unesite sifru artikla: ";
		std::string article_code = input();
		processingArticleReports(article_code);
	}
	else if (option4 == '2')
	{
		std::string date1, date2, article;
		int p = 0;
		do {
			system("cls");
			logoS();
			std::cout << std::endl << "PREGLED ZA ODREDJEN VREMENSKI INTERVAL" << std::endl;
			std::cout << std::endl;
			std::cout << "Artikal: ";
			article = input();
			std::cout << std::endl;

			std::string path = "Artikli/" + article + ".txt";
			std::ifstream f(path.c_str());

			std::cout << std::endl << "Unesite datum u obliku: dan.mjesec.godina" << std::endl << std::endl;
			std::cout << "Datum od: ";
			std::cin >> date1;
			std::cout << "Datum do: ";
			std::cin >> date2;

			int num1, num2;
			num1 = parseDate(date1);
			num2 = parseDate(date2);

			if (checkDate(date1) && checkDate(date2) && num1 <= num2 && f)
			{
				articleReport(article, num1, num2);
				p = 1;
			}
			else if (!f)
			{
				std::cout << std::endl << "Uneseni artikal se ne nalazi u evidenciji" << std::endl;
				std::cout << "Pritisnite enter za novi unos" << std::endl;
				getchar();
				getchar();
				system("cls");
			}
			else if (!checkDate(date1))
			{
				std::cout << std::endl << "Prvi datum nije validan" << std::endl;
				std::cout << "Pritisnite enter za novi unos" << std::endl;
				getchar();
				getchar();
				system("cls");
			}
			else if (!checkDate(date2))
			{
				std::cout << std::endl << "Drugi datum nije validan" << std::endl;
				std::cout << "Pritisnite enter za novi unos" << std::endl;
				getchar();
				getchar();
				system("cls");
			}
			else
			{
				std::cout << std::endl << "Drugi datum se nalazi ispred prvog" << std::endl;
				std::cout << "Pritisnite enter za novi unos" << std::endl;
				getchar();
				getchar();
				system("cls");
			}
		} while (p != 1);



		getchar();
		getchar();
	}

}

void monthSaldoReport()//funkcija za unos montha i godine
{
	std::string month, year;
	do//meni za izbor montha
	{

		system("cls");
		logoS();
		std::cout << std::endl << "MJESECNI IZVJESTAJ" << std::endl << std::endl;
		std::cout << std::endl << " 1. Januar          2. Februar         3. Mart" << std::endl;
		std::cout << " 4. April           5. Maj             6. Jun" << std::endl;
		std::cout << " 7. Jul             8. Avgust          9. Septembar" << std::endl;
		std::cout << "10. Oktobar        11. Novembar       12. Decembar" << std::endl;
		std::cout << std::endl << "Unesi opciju: "; std::cin >> month;
	} while (month != "1" && month != "2" && month != "3" && month != "4" && month != "5" && month != "6" &&
		month != "7" && month != "8" && month != "9" && month != "10" && month != "11" && month != "12");

	system("cls");
	logoS();
	std::cout << std::endl;
	std::cout << std::endl;
	int m, y;
	m = stoi(month);
	do
	{
		std::cout << "Unesite godinu: "; std::cin >> year;
		y = stoi(year);
		if (y < 0)
		{
			std::cout << std::endl << "Unesena godina nije validna. Pritisnite 'Enter' da pokusate ponovo." << std::endl;
			getchar();
			getchar();
			system("cls");
			logoS();
			std::cout << std::endl;

		}
	} while (y < 0);




	if (month == "1")
	{
		system("cls");
		logoS();


		std::cout << std::endl << "JANUAR" << std::endl;


	}

	if (month == "2")
	{
		system("cls");
		logoS();

		std::cout << std::endl << "FEBRUAR" << std::endl;

	}
	if (month == "3")
	{
		system("cls");
		logoS();

		std::cout << std::endl << "MART" << std::endl;

	}
	if (month == "4")
	{
		system("cls");
		logoS();

		std::cout << std::endl << "APRIL" << std::endl;

	}
	if (month == "5")
	{
		system("cls");
		logoS();

		std::cout << std::endl << "MAJ" << std::endl;

	}
	if (month == "6")
	{
		system("cls");
		logoS();

		std::cout << std::endl << "JUN" << std::endl;

	}
	if (month == "7")
	{
		system("cls");
		logoS();

		std::cout << std::endl << "JUL" << std::endl;

	}
	if (month == "8")
	{
		system("cls");
		logoS();

		std::cout << std::endl << "AVGUST" << std::endl;

	}
	if (month == "9")
	{
		system("cls");
		logoS();

		std::cout << std::endl << "SEPTEMBAR" << std::endl;

	}
	if (month == "10")
	{
		system("cls");
		logoS();

		std::cout << std::endl << "OKTOBAR" << std::endl;

	}
	if (month == "11")
	{
		system("cls");
		logoS();

		std::cout << std::endl << "NOVEMBAR" << std::endl;

	}
	if (month == "12")
	{
		system("cls");
		logoS();

		std::cout << std::endl << "DECEMBAR" << std::endl;

	}



	Monthly(m, y);

}


std::string input() {
	char a;
	char temp[35];
	int i = 0;
	std::string str;
	while (1) {
		a = _getch();
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9') || a == ' ' || a == '_' || a == '.' || a == '#' || a == '$' || a == '@' || a == '!' || a == '%' || a == '^' || a == '&' || a == '*' || a == '(' || a == ')' || a == '-' || a == '=' || a == '+') {
			temp[i++] = a;
			std::cout << a;
		}
		if (a == '\b' && i > 0) {
			std::cout << "\b \b";
			i--;
		}
		if (a == '\r') {
			temp[i] = '\0';
			break;
		}
	}
	str = temp;
	return str;
}