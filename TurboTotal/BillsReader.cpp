#include "BillsReader.h"
#include <iomanip>
#include <Windows.h>
#include "Format3.h"
#include "Format2.h"

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

void putArticles(std::string name,std::string buyer_name,std::string date)
{
	std::ifstream file("Racuni/" + name);
	std::string line, pom,new_line_string;
	int new_line_counter = 0;
	getline(file, new_line_string);
	while (getline(file, line) )
	{
		int i = 0;
		std::string code, amount, price, total;

		for (i = 0; i < line.length(); i++)
			if (line[i] != ';')
				code += line[i];
			else break;
			i++;
		for (i; i < line.length(); i++)
				if (line[i] != ';')
					amount += line[i];
				else break;
				i++;
		for (i; i < line.length(); i++)
					if (line[i] != ';')
						price += line[i];
					else break;
					i++;
	    for (i; i < line.length(); i++)
						if (line[i] != ';')
							total += line[i];
						else break;

						std::ofstream article("Artikli/"+ code + ".txt",std::ios::app);
						article << buyer_name << std::endl << date << std::endl;
						article << amount << " " << price << " " << total << std::endl;
						article << "----------------------------------" << std::endl;
						code.erase();
						amount.erase();
						price.erase();
						total.erase();
	}
	file.close();

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
		if (line == "Racun") std::cout << "Format 1" << std::endl;
		else if (line == "Maloprodajni") { bills[i].erase(0, 7);  format2Processing(bills[i]); }
		else if (line == "Datum:") { format3(bills[i]); }
		else if (line == "OSI") std::cout << "Format 4" << std::endl;
		else
		{
			bills[i].erase(0, 7);
			format5Processing(bills[i]);
		}
	}
	return 1;
}

int validation(std::string name)
{
	std::ifstream file("Racuni/" + name);
	std::string line, pom, new_line_string;
	int new_line_counter = 0;
	getline(file, new_line_string);
	while (getline(file, line))
	{
		int i = 0;
		std::string code, amount, price, total;

		for (i = 0; i < line.length(); i++)
			if (line[i] != ';')
				code += line[i];
			else break;
			i++;
			for (i; i < line.length(); i++)
				if (line[i] != ';')
					amount += line[i];
				else break;
				i++;
				for (i; i < line.length(); i++)
					if (line[i] != ';')
						price += line[i];
					else break;
					i++;
					for (i; i < line.length(); i++)
						if (line[i] != ';')
							total += line[i];
						else break;
						std::string::size_type sz;
						double double_amount = stod(amount, &sz);
						double double_price = stod(price, &sz);
						double double_total = stod(total, &sz);
						if (double_amount*double_price != double_total)
							return 0;
						code.erase();
						amount.erase();
						price.erase();
						total.erase();
	}
	file.close();
	return 1;
}

void format5Processing(std::string name)
{
	if (validation(name))
	{
		std::string buyer_name, buyer_txt, date;

		findNameSurnameDate(name, buyer_name, date);

		buyer_txt = "Kupci/" + buyer_name + ".txt";//omoguceno da bude otvoreno/dopisano u .txt fajl pod datim imenom u folderu 'Kupci'

		std::ofstream buyer_file(buyer_txt, std::ios::app);

		buyer_file << date << std::endl;//unesen datum u txt fajl ImePrezime

		findArticles(name, buyer_txt);
		putArticles(name, buyer_name, date);

		std::ofstream processed_file("Obradjeni_racuni/" + name);
		std::ifstream old_file("Racuni/" + name);
		std::string line;
		while (getline(old_file, line))
			processed_file << line << std::endl;

		buyer_file.close();
		processed_file.close();
		old_file.close();
	}
	else
	{
		std::string error_file = "Error/" + name.erase(name.length() - 4, name.length());
		error_file += "_error.txt";
		std::ofstream processed_file(error_file);
		processed_file << "Greska u obracunu: kolicina*cijena=ukupno nije dobro obracunato!!!" << std::endl;
	}
}
void findNameSurnameDate(std::string name, std::string& buyer_name, std::string&date)
{
	int i;
	for (i = 0; i < name.length() && name[i] != '#'; i++)
		buyer_name += name[i];
	i += 1;
	for (i; i < name.length() && name[i] != 'c'; i++)
		date += name[i];
}

void findArticles(std::string name, std::string buyer_txt)
{
	std::ifstream file("Racuni/" + name);
	double total = 0;
	double double_price;
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
						std::string::size_type sz;
					    double_price = stod(pom, &sz);
						total += double_price;
						buyer_file << std::endl;
						new_line_counter = 0;
					}
					pom.erase();
				}
		}
	}
	buyer_file <<std::setw(2)<< total-total*0.17 << std::endl;
	buyer_file << std::setw(2) << total*0.17<<std::endl;
	buyer_file << std::setw(2) << total<<std::endl;
	buyer_file << "------------------------------" << std::endl;
	buyer_file.close();
}
