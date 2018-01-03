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
	std::ifstream file(bill);
	file.seekg(0, file.beg);
	std::string trash, st1, st2, st;
	double kol, cijena, ukupno;
	std::string kupac, datum;
	double total, pdv, totalp;
	int day, month, year;

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
	

	for (int i = 0; i < 9; i++)
		std::getline(file, trash);

	parseDate(datum, day, month, year);

	std::ofstream kupci("Kupci/" + kupac + ".txt", std::ios::app);
	kupci << day << "." << month << "." << "year" << std::endl;

	while (file >> st1 >> trash && st1[0] != '-') {

		trash.push_back('=');

		int i = 0;
		while (!(trash[i] == '=')) {
			st2.push_back(trash[i]);
			i++;
		}

		st = st2 + ' ' + st1;

		boi(trash, st2, kol, i);
		boi(trash, st2, cijena, i);
		boi(trash, st2, ukupno, i);

		kupci << st << " " << kol << " " << cijena << " " << ukupno << std::endl;
		trash.clear();
		st2.clear();
	}

	kupci << total << std::endl << pdv << std::endl << totalp << std::endl;
	kupci << "--------------------------" << std::endl;
	file.close();
	kupci.close();
}