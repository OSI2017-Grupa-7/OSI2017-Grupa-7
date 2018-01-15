#include "BillsReader.h"
#include <iomanip>
#include <Windows.h>
#include "Format1.h"
#include "Format2.h"
#include "Format3.h"
#include "Format4.h"
#include "format5.h"
#include "Format1.h"


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

void removeBillProcessed(std::vector<std::string> bills)
{
	for (unsigned int i = 0; i < bills.size(); i++)
	{
		char * writable = new char[bills[i].size() + 1];
		std::copy(bills[i].begin(), bills[i].end(), writable);
		writable[bills[i].size()] = '\0';
		remove(writable);
		delete[]writable;
	}
}



void billsReading()
{
	std::vector<std::string> bills = get_filenames("Racuni");
	billFormat(bills);//delegirajuca fja za svaki od formata
	removeBillProcessed(bills);//fja koja remove-a obradjene racune
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
		if (line == "Racun") { bills[i].erase(0, 7); format1(bills[i]); }
		else if (line == "Maloprodajni") { bills[i].erase(0, 7); format2Processing(bills[i]); }
		else if (line == "Datum:") { format3(bills[i]); }
		else if (line == "OSI") { readformat4(bills[i]); }
		else { bills[i].erase(0, 7);format5Processing(bills[i]);}
	}
	return 1;
}

