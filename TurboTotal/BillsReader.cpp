#include "BillsReader.h"
#include <iomanip>
#include <Windows.h>

std::vector<std::string> get_filenames(std::experimental::filesystem::path path)
{
	namespace stdfs = std::experimental::filesystem;
	std::vector<std::string> filenames;
	const stdfs::directory_iterator end{};
	for (stdfs::directory_iterator iter{ path }; iter != end; ++iter)
	{
		if (stdfs::is_regular_file(*iter)) // comment out if all names (names of directories tc.) are required
			filenames.push_back(iter->path().string());
	}
	return filenames;
}


void billsReading()
{
	std::vector<std::string> bills = get_filenames("Racuni");
	//treba onemoguciti da se citaju racuni koji su prethodno obradjeni
	billFormat(bills);
}

int billFormat(std::vector<std::string> bills)
{
	for (unsigned int i = 0; i < bills.size(); i++)
	{
		std::string line;
		std::ifstream file(bills[i]);
		for (int j = 0; j < 3; j++)
			std::getline(file, line);
		file >> line;
		if (line == "Racun") std::cout << "Format 1" << std::endl;
		else if (line == "Maloprodajni") std::cout << "Format 2" << std::endl;
		else if (line == "Datum:") std::cout << "Format 3" << std::endl;
		else if (line == "OSI") std::cout << "Format 4" << std::endl;
		else
		{
			bills[i].erase(0, 7);
			format5Processing(bills[i]);
		}
	}
	return 1;
}

void format5Processing(std::string name)
{
	std::string buyer_name, buyer_txt, date;

	findNameSurnameDate(name, buyer_name, date);

	buyer_txt = "Kupci/" + buyer_name + ".txt";//omoguceno da bude otvoreno/dopisano u .txt fajl pod datim imenom u folderu 'Kupci'

	std::ofstream buyer_file(buyer_txt, std::ios::app);

	buyer_file << date << std::endl;//unesen datum u txt fajl ImePrezime

	findArticles(name, buyer_txt);

	std::ofstream processed_file("Obradjeni_racuni/" + name);
	std::ifstream old_file("Racuni/" + name);
	std::string line;
	while (getline(old_file, line))
		processed_file << line << std::endl;
}

void findNameSurnameDate(std::string name, std::string& buyer_name, std::string&date)
{
	int i;
	for (i = 0; i < name.length() && name[i] != '_'; i++)
		buyer_name += name[i];

	i += 1;
	for (i; i < name.length() && name[i] != 'c'; i++)
		date += name[i];
}

void findArticles(std::string name, std::string buyer_txt)
{
	std::ifstream file("Racuni/" + name);
	int new_line_counter = 0;
	file.seekg(30);
	std::ofstream buyer_file(buyer_txt, std::ios::app);
	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			std::string pom;
			for (int i = 0; i < line.length(); i++)
				if (line[i] != ';')
					pom += line[i];
				else
				{
					new_line_counter += 1;
					buyer_file << pom << " ";
					if (new_line_counter > 3)
					{
						buyer_file << std::endl;
						new_line_counter = 0;
					}
					pom.erase();
				}
		}
	}
	buyer_file << "------------------------------" << std::endl;
}
