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
	double kol, cijena, ukupno;// pomocne promjenljive za ucitavanje
	std::vector<std::string> st2V;// vektor sifri artikala
	std::vector<double> kolV, cijenaV, ukupnoV;// vektori za smjestanje informacija o kolicini, cijeni i kolicina*cijena
	std::string kupac, datum;//pomocne promjenljive
	double total, pdv, totalp;// informacije ucitane sa racuna: ukupno bez pdv-a, obracunat pdv, ukupno + obracunat pdv
	int day, month, year;// posebne promjenljive za datum
	int count = 0;// brojac za broj ucitanih artikala
	double sum = 0;// promjenljiva za provjeru ucitane ukupne vrijednosti racuna
	bill.erase(0, 7);//brisanje putanje Racuni/ kao bi se moglo koristi ime datoteke

	/*std::string rac = "Racuni/" + bill, err = "Error/" + bill, obr = "Obradjeni_racuni/" + bill;
	const char* rac_path = rac.c_str();
	const char* err_path = err.c_str();
	const char* obr_path = obr.c_str();*/

	///////////////izdvajanje potrebnih informacija iz ucitane datoteke
	GotoLine(file, 3);
	file >> trash >> kupac;
	file.seekg(0, file.beg);
	GotoLine(file, 4);
	file >> trash >> datum;
	file.seekg(0, file.beg);
	GotoLine(file, 14);
	file >> trash >> total >> trash >> pdv;
	file.seekg(0, file.beg);
	GotoLine(file, 16);
	file >> trash >> trash >> trash >> totalp;
	file.seekg(0, file.beg);
	
	///////////ako je tacan uslov, ucitana datoteka se premjesta u Error folder
	if (totalp != total + pdv) {
		file.close();
		std::string error_file = "Error/" + bill.erase(bill.length() - 4, bill.length());
		error_file += "_error.txt";
		std::ofstream processed_file(error_file);
		processed_file << "Greska u obracunu: Ukupna cijena = Ukupno + PDV nije dobro obracunato!!!" << std::endl;
		//rename(rac_path, err_path);
		return;
	}

	///////////ako je tacan uslov, ucitana datoteka se premjesta u Error folder
	if (total * 0.17 != pdv) {
		file.close();
		std::string error_file = "Error/" + bill.erase(bill.length() - 4, bill.length());
		error_file += "_error.txt";
		std::ofstream processed_file(error_file);
		processed_file << "Greska u obracunu: PDV = 0.17 * Ukupno nije dobro obracunato!!!" << std::endl;
		return;
	}

	for (int i = 0; i < 9; i++)
		std::getline(file, trash);

	parseDate(datum, day, month, year);

	/////////// izdvajanje potrebnih informacija u pomocne promjenljive i dodavanje u vektore sve dok se ne dodje do -
	while (file >> st1 >> trash && st1[0] != '-') {

		trash.push_back('=');

		int i = 0;
		while (!(trash[i] == '=')) {
			st2.push_back(trash[i]);
			i++;
		}

		st2V.push_back(st2);
		st.push_back(st2 + ' ' + st1);
		count++;

		parse(trash, st2, kol, i);
		parse(trash, st2, cijena, i);
		parse(trash, st2, ukupno, i);

		///////////ako je tacan uslov, ucitana datoteka se premjesta u Error folder
		if (ukupno != cijena * kol) {
			file.close();
			std::string error_file = "Error/" + bill.erase(bill.length() - 4, bill.length());
			error_file += "_error.txt";
			std::ofstream processed_file(error_file);
			processed_file << "Greska u obracunu: Ukupno = Cijena * Kolicina nije dobro obracunato!!!" << std::endl;
			return;
		}

		kolV.push_back(kol); cijenaV.push_back(cijena); ukupnoV.push_back(ukupno);
		trash.clear();
		st2.clear();
	}

	for (int i = 0; i < count; i++)
		sum = sum + ukupnoV[i];
	///////////ako je tacan uslov, ucitana datoteka se premjesta u Error folder
	if (sum != total) {
		file.close();
		std::string error_file = "Error/" + bill.erase(bill.length() - 4, bill.length());
		error_file += "_error.txt";
		std::ofstream processed_file(error_file);
		processed_file << "Greska u obracunu: kolicina*cijena=ukupno nije dobro obracunato!!!" << std::endl;
		//rename(rac_path, err_path);
		return;
	}
	/////////////ispis ucitanih informacija u odredjene datoteke 
	std::ofstream kupci("Kupci/" + kupac + ".txt", std::ios::app);// kreiranje datoteke sa imenom kupca u folder Kupci
	kupci << day << "." << month << "." << year << std::endl;
	////////////petlja za formiranje datoteka za artikle u koju se upisuju odredjene informacije za artikal i kupca
	for (int i = 0; i < count; i++) {
		std::ofstream article("Artikli/" + st2V[i] + ".txt", std::ios::app);
		article << kupac << std::endl << day << "." << month << "." << year << std::endl << kolV[i] << " " << cijenaV[i] << " " << ukupnoV[i] << std::endl;
		article << "---------------------------" << std::endl;
		article.close();
		article.clear();
		kupci << st[i] << " " << kolV[i] << " " << cijenaV[i] << " " << ukupnoV[i] << std::endl;
	}
	kupci << total << std::endl << pdv << std::endl << totalp << std::endl;
	kupci << "--------------------------" << std::endl;
	file.close();
	kupci.close();
	/////////////prebacivanje ucitane datoteke iz foldera Racuni u Obradjeni_racuni jer nema gresaka u datoteci
	std::ofstream processed_file("Obradjeni_racuni/" + bill);
	std::ifstream old_file("Racuni/" + bill);
	std::string line;
	while (getline(old_file, line))
		processed_file << line << std::endl;
}