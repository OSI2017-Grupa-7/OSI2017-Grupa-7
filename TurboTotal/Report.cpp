#include "Report.h"
#include  "Logo.h"

void buyerReport()
{
	system("cls");
	logoS();
	std::string ime, prezime;
	std::cout <<std::endl<< "IZVJESTAJ PO KUPCU" << std::endl << std::endl;
	std::cout << "Unesite ime i prezime kupca: "<<std::endl;
	std::cout << std::endl << "Ime: ";  std::cin >> ime;
	std::cout << std::endl << "Prezime: "; std::cin >> prezime;
	//uci u bazu kupaca i ispisati izvjestaj
}

void productReport()
{
	system("cls");
	logoS();
	std::cout <<std::endl<< "IZVJESTAJ PO ARTIKLU" << std::endl<<std::endl;
	std::string naziv;
	std::cout << "Unesite naziv artikla: " << std::endl;
	std::cout << std::endl << "Naziv: ";  std::cin >> naziv;
	//uci u bazu artikala i ispisati izvjestaj
}

void monthSaldoReport()
{
	system("cls");
	logoS();
	std::string mjesec;
	std::cout <<std::endl<< "MJESECNI IZVJESTAJ" << std::endl<<std::endl;
	std::cout << "Unesite naziv mjeseca: ";std::cin>>mjesec;
	//uci u bazu artikala i ispisati izvjestaj
}
