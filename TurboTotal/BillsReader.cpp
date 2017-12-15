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
	std::vector<std::string> bills = get_filenames("C:/Users/Susnjar/Desktop/Projektni_zadatak/TurboTotal/Racuni");
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