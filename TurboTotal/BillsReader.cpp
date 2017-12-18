#include "BillsReader.h"

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
	for (unsigned int i = 0; i < bills.size(); i++)
	{
		std::string line;
		std::ifstream file(bills[i]);
		std::cout << std::endl << "=====================================================" << std::endl;
		std::cout << "Racun: " << i + 1;
		std::cout << std::endl << "=====================================================" << std::endl;
		while (getline(file, line))
		{
			std::cout << line<<std::endl;
		}
	}
	
	getchar();
	getchar();
}

int billFormat()
{
	std::vector<std::string> bills = get_filenames("Racuni");
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
		else std::cout << "Format 5" << std::endl;


	}

	getchar();
	getchar();
	return 1;
}