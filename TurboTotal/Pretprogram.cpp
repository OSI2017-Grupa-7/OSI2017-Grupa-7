#include <iostream>
#include <fstream>
#include <string>
#include "Pretprogram.h"

void Pretprogram()
{
	std::string line;
	std::string one = "1";
	std::ifstream myfile("1.txt");
	if (myfile.is_open())
	{
		getline(myfile, line);
		if (line == one)
		{
			char valuta;
			myfile.close();
			std::ofstream file;
			file.open("1.txt");
			file << "0";
			do
			{
				system("cls");
				std::cout << "Dobrodosli u pretprogram koji se pokrece samo pri prvom pokretanju aplikacije na racunaru." << std::endl;
				std::cout << "Ovdje se vrsi odabir valute koju ce aplikacija koristit tokom rada." << std::endl;
				std::cout << "Odabir valute vrsi administrator koji je prvi dobio pristup sistemu." << std::endl;

				std::cout << std::endl << "ODABERI VALUTU: " << std::endl;
				std::cout << std::endl << "1. Americki dolar" << std::endl;
				std::cout << "2. Evro" << std::endl;
				std::cout << "3. BiH KM" << std::endl;
				std::cout << "4. Srbijanski dinar" << std::endl;
				std::cout << "5. Britanska funta" << std::endl;
				std::cout << std::endl << "Odaberi opciju: "; std::cin >> valuta;
			} while (valuta != 1 && valuta != 2 && valuta != 3 && valuta != 4 && valuta != 5);
			if (valuta == 1)
			{
				std::ofstream value;
				value.open("Valuta.txt");
				value << "$";
				value.close();
			}
			if (valuta == 2)
			{
				std::ofstream value;
				value.open("Valuta.txt");
				value << "€";
				value.close();
			}
			if (valuta == 3)
			{
				std::ofstream value;
				value.open("Valuta.txt");
				value << "BAM";
				value.close();
			}
			if (valuta == 4)
			{
				std::ofstream value;
				value.open("Valuta.txt");
				value << "RSD";
				value.close();
			}
			if (valuta == 5)
			{
				std::ofstream value;
				value.open("Valuta.txt");
				value << "GBP";
				value.close();
			}
			getchar();
		}
	}
}