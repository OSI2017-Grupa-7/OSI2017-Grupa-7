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


void boi(std::string& trash, std::string& st2, double& kol, int& i) {
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
	std::ifstream file("Racuni/" + bill);
	file.seekg(0, file.beg);
	std::string trash, st1, st2;
	std::vector<std::string> st;
	double kol, cijena, ukupno;
	std::vector<double> kolV, cijenaV, ukupnoV;
	std::string kupac, datum;
	double total, pdv, totalp;
	int day, month, year;
	int count = 0;
	double sum = 0;
	std::string rac = "Racuni/" + bill, err = "Error/" + bill, obr = "Obradjeni_racuni/" + bill;
	const char* rac_path = rac.c_str();
	const char* err_path = err.c_str();
	const char* obr_path = obr.c_str();

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
	
	if (totalp != total + pdv) {
		file.close();
		rename(rac_path, err_path);
		return;
	}

	for (int i = 0; i < 9; i++)
		std::getline(file, trash);

	parseDate(datum, day, month, year);

	while (file >> st1 >> trash && st1[0] != '-') {

		trash.push_back('=');

		int i = 0;
		while (!(trash[i] == '=')) {
			st2.push_back(trash[i]);
			i++;
		}

		st.push_back(st2 + ' ' + st1);
		count++;

		boi(trash, st2, kol, i);
		boi(trash, st2, cijena, i);
		boi(trash, st2, ukupno, i);

		kolV.push_back(kol); cijenaV.push_back(cijena); ukupnoV.push_back(ukupno);
		trash.clear();
		st2.clear();
	}

	for (int i = 0; i < count; i++)
		sum = sum + ukupnoV[i];

	if (sum != total) {
		file.close();
		rename(rac_path, err_path);
		return;
	}

	std::ofstream kupci("Kupci/" + kupac + ".txt", std::ios::app);

	for (int i = 0; i < count; i++)
		kupci << st[i] << " " << kolV[i] << " " << cijenaV[i] << " " << ukupnoV[i] << std::endl;
	kupci << day << "." << month << "." << "year" << std::endl;
	kupci << total << std::endl << pdv << std::endl << totalp << std::endl;
	kupci << "--------------------------" << std::endl;
	file.close();
	kupci.close();
	rename(rac_path, obr_path);
}