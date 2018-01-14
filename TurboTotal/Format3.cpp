#include "Format3.h"

void parseDate(const std::string& string, int& day, int& month, int& year) {
	std::sscanf(string.c_str(), "%d/%d/%d", &day, &month, &year);
}


std::ifstream& GotoLine(std::ifstream& file, unsigned int num) {
	file.seekg(std::ios::beg);
	for (int i = 0; i < num - 1; ++i) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return file;
}


void parse(std::string& trash, std::string& st2, double& kol, int& i) {
	while (trash[i] == '=')
		i++;

	st2.clear();

	while (!(trash[i] == '=')) {
		st2.push_back(trash[i]);
		i++;
	}

	kol = atof(st2.c_str());
}


void format3(std::string& bill) {
	std::ifstream file(bill);//ucitavanje datoteke
	file.seekg(0, file.beg);//postavljanje pokazivaca na pocetak
	std::string trash, st1, st2;//pomocne promjenljive
	std::vector<std::string> st;// vektor stringova u kojem se smjestaju ime i sifra artikla
	double ammount, price, tot;// pomocne promjenljive za ucitavanje
	std::vector<double> ammountV, priceV, totV;// vektori za smjestanje informacija o kolicini, cijeni i kolicina*cijena
	std::string buyer, date;//pomocne promjenljive
	double total, pdv, totalp;// informacije ucitane sa racuna: ukupno bez pdv-a, obracunat pdv, ukupno + obracunat pdv
	int day, month, year;// posebne promjenljive za datum
	int count = 0;// brojac za broj ucitanih artikala
	double sum = 0;// promjenljiva za provjeru ucitane ukupne vrijednosti racuna
	bill.erase(0, 7);//brisanje putanje Racuni/ kao bi se moglo koristi ime datoteke
	int n = 0, r = 0;// brojac za broj linija koji ima do -
	/*std::string rac = "Racuni/" + bill, err = "Error/" + bill, obr = "Obradjeni_racuni/" + bill;
	const char* rac_path = rac.c_str();
	const char* err_path = err.c_str();
	const char* obr_path = obr.c_str();*/

	///////////////izdvajanje potrebnih informacija iz ucitane datoteke
	GotoLine(file, 3);
	std::getline(file, buyer);
	buyer.erase(0, 7);
	//file >> trash >> buyer;
	file.seekg(0, file.beg);
	GotoLine(file, 4);
	file >> trash >> date;
	file.seekg(0, file.beg);
	while (r != 2) 
	{
		std::getline(file, trash);
		n++;
		if (trash[0] == '-')
			r++;
	}
	file.seekg(0, file.beg);
	GotoLine(file, n + 2);
	file >> trash >> total >> trash >> pdv;
	file.seekg(0, file.beg);
	GotoLine(file, n + 4);
	file >> trash >> trash >> trash >> totalp;
	file.seekg(0, file.beg);
	
	for (int i = 0; i < 9; i++)
		std::getline(file, trash);

	parseDate(date, day, month, year);

	/////////// izdvajanje potrebnih informacija u pomocne promjenljive i dodavanje u vektore sve dok se ne dodje do -
	while (file >> st1 >> trash && st1[0] != '-') {

		trash.push_back('=');

		int i = 0;
		while (!(trash[i] == '=')) {
			st2.push_back(trash[i]);
			i++;
		}

		st.push_back(st1 + ' ' +  st2);
		count++;

		parse(trash, st2, ammount, i);
		parse(trash, st2, price, i);
		parse(trash, st2, tot, i);

		///////////ako je tacan uslov, ucitana datoteka se premjesta u Error folder
		if (tot != price * ammount) {
			file.close();
			std::string error_file = "Error/" + bill.erase(bill.length() - 4, bill.length());
			error_file += "_error.txt";
			std::ofstream processed_file(error_file);
			processed_file << "Racun sadrzi gresku-ukupna vrijednost (kolicina*cijena) za jedan od artikala nije ispravna." << std::endl;
			return;
		}

		ammountV.push_back(ammount); priceV.push_back(price); totV.push_back(tot);
		trash.clear();
		st2.clear();
	}

	for (int i = 0; i < count; i++)
		sum = sum + totV[i];
	///////////ako je tacan uslov, ucitana datoteka se premjesta u Error folder
	if (sum != total) {
		file.close();
		std::string error_file = "Error/" + bill.erase(bill.length() - 4, bill.length());
		error_file += "_error.txt";
		std::ofstream processed_file(error_file);
		processed_file << "Racun sadrzi gresku-ukupna vrijednost(bez PDV-a) nije dobro izracunata." << std::endl;
		//rename(rac_path, err_path);
		return;
	}

	///////////ako je tacan uslov, ucitana datoteka se premjesta u Error folder
	else if ((total * 0.17) != pdv) {
		file.close();
		std::string error_file = "Error/" + bill.erase(bill.length() - 4, bill.length());
		error_file += "_error.txt";
		std::ofstream processed_file(error_file);
		processed_file << "Racun sadrzi gresku-PDV nije dobro izracunat." << std::endl;
		return;
	}

	///////////ako je tacan uslov, ucitana datoteka se premjesta u Error folder
	else if (totalp != total + pdv) {
		file.close();
		std::string error_file = "Error/" + bill.erase(bill.length() - 4, bill.length());
		error_file += "_error.txt";
		std::ofstream processed_file(error_file);
		processed_file << "Racun sadrzi gresku-ukupna vrijednost za placanje(pdv+ukupno) nije dobro izracunata." << std::endl;
		//rename(rac_path, err_path);
		return;
	}

	/////////////ispis ucitanih informacija u odredjene datoteke 
	std::ofstream buyers("Kupci/" + buyer + ".txt", std::ios::app);// kreiranje datoteke sa imenom kupca u folder Kupci
	buyers << day << "." << month << "." << year << "." << std::endl;
	////////////petlja za formiranje datoteka za artikle u koju se upisuju odredjene informacije za artikal i kupca
	for (int i = 0; i < count; i++) {
		std::ofstream article("Artikli/" + st[i] + ".txt", std::ios::app);
		article << buyer << std::endl << day << "." << month << "." << year << "." << std::endl << ammountV[i] << " " << priceV[i] << " " << totV[i] << std::endl;
		article << "---------------------------" << std::endl;
		article.close();
		article.clear();
		buyers << st[i] << " " << ammountV[i] << " " << priceV[i] << " " << totV[i] << std::endl;
	}
	buyers << total << std::endl << pdv << std::endl << totalp << std::endl;
	buyers << "--------------------------" << std::endl;
	file.close();
	buyers.close();
	/////////////prebacivanje ucitane datoteke iz foldera Racuni u Obradjeni_racuni jer nema gresaka u datoteci
	std::ofstream processed_file("Obradjeni_racuni/" + bill);
	std::ifstream old_file("Racuni/" + bill);
	std::string line;
	while (getline(old_file, line))
		processed_file << line << std::endl;
}