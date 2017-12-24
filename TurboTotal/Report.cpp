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

	std::cout << std::endl << "IZVJESTAJ ZA KUPCA: " << ime << " " << prezime << std::endl;
	//uci u bazu kupaca i ispisati izvjestaj
}

void productReport()
{
	system("cls");
	logoS();
	std::cout <<std::endl<< "IZVJESTAJ PO ARTIKLU" << std::endl<<std::endl;
	std::string sifra;
	std::cout << "Unesite sifru artikla: " << std::endl;
	std::cout << std::endl << "Sifra: ";  std::cin >> sifra;


	std::cout << std::endl << "IZVJESTAJ ZA ARTIKAL: " << sifra <<std::endl;

	//uci u bazu artikala i ispisati izvjestaj
}

void monthSaldoReport()
{
	std::string mjesec;
	do
	{

		system("cls");
	logoS();
	std::cout << std::endl << "MJESECNI IZVJESTAJ" << std::endl << std::endl;
	std::cout << std::endl << " 1. Januar          2. Februar         3. Mart" << std::endl;
	std::cout << " 4. April           5. Maj             6. Jun" << std::endl;
	std::cout << " 7. Jul             8. Avgust          9. Septembar" << std::endl;
	std::cout << "10. Oktobar        11. Novembar       12. Decembar" << std::endl;
	std::cout << std::endl << "Unesi opciju: "; std::cin >> mjesec;
	} while (mjesec != "1" && mjesec != "2" && mjesec != "3" && mjesec != "4" && mjesec != "5" && mjesec != "6" &&
		mjesec != "7" && mjesec != "8" && mjesec != "9" && mjesec != "10" && mjesec != "11" && mjesec != "12");
	if (mjesec == "1")
	{
		system("cls");
		logoS();
		std::cout << std::endl << "JANUAR"<<std::endl;
	}
	if (mjesec == "2")
	{
		system("cls");
		logoS();
		std::cout << std::endl << "FEBRUAR" << std::endl;
	}
	if (mjesec == "3")
	{
		system("cls");
		logoS();
		std::cout << std::endl << "MART" << std::endl;
	}
	if (mjesec == "4")
	{
		system("cls");
		logoS();
		std::cout << std::endl << "APRIL" << std::endl;
	}
	if (mjesec == "5")
	{
		system("cls");
		logoS();
		std::cout << std::endl << "MAJ" << std::endl;
	}
	if (mjesec == "6")
	{
		system("cls");
		logoS();
		std::cout << std::endl << "JUN" << std::endl;
	}
	if (mjesec == "7")
	{
		system("cls");
		logoS();
		std::cout << std::endl << "JUL" << std::endl;
	}
	if (mjesec == "8")
	{
		system("cls");
		logoS();
		std::cout << std::endl << "AVGUST" << std::endl;
	}
	if (mjesec == "9")
	{
		system("cls");
		logoS();
		std::cout << std::endl << "SEPTEMBAR" << std::endl;
	}
	if (mjesec == "10")
	{
		system("cls");
		logoS();
		std::cout << std::endl << "OKROBAR" << std::endl;
	}
	if (mjesec == "11")
	{
		system("cls");
		logoS();
		std::cout << std::endl << "NOVEMBAR" << std::endl;
	}
	if (mjesec == "12")
	{
		system("cls");
		logoS();
		std::cout << std::endl << "DECEMBAR" << std::endl;
	}
//uci u bazu artikala i ispisati izvjestaj
}
