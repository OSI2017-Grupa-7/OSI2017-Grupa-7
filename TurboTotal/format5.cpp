#include "format5.h"

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
		std::ifstream error_bill("Racuni/" + name);
		std::ofstream new_error_file("Racuni_sa_greskom/" + name);
		std::string line;
		while (getline(error_bill, line))
		{
			new_error_file << line << std::endl;
		}
		new_error_file.close();
		std::string error_file = "Error/" + name.erase(name.length() - 4, name.length());
		error_file += "_error.txt";
		std::ofstream processed_file(error_file);
		processed_file << "Racun sadrzi gresku-ukupna vrijednost (kolicina*cijena) za jedan od artikala nije ispravna." << std::endl;
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
	double total_total = 0;
	double double_price;
	std::string line;
	getline(file, line);
	std::ofstream buyer_file(buyer_txt, std::ios::app);
	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			int i = 0;
			std::string code, amount, price, total;

			for (i = 0; i < line.length(); i++)
				if (line[i] != ';')
					code += line[i];
				else break;
				buyer_file << code << " ";
				i++;
				for (i; i < line.length(); i++)
					if (line[i] != ';')
						amount += line[i];
					else break;
					buyer_file << amount << " ";

					i++;
					for (i; i < line.length(); i++)
						if (line[i] != ';')
							price += line[i];
						else break;

						buyer_file << price << " ";
						i++;
						for (i; i < line.length(); i++)
								total += line[i];
						buyer_file << total << std::endl;
							std::string::size_type sz;
		
							double double_total = stod(total, &sz);
							total_total += double_total;
								
							code.erase();
							amount.erase();
							price.erase();
							total.erase();
		}
	}
	buyer_file << std::setw(2) << total_total << std::endl;
	buyer_file << std::setw(2) <<total_total*0.17 << std::endl;
	buyer_file << std::setw(2) << total_total+total_total*0.17 << std::endl;
	buyer_file << "------------------------------" << std::endl;
	buyer_file.close();
}

void putArticles(std::string name, std::string buyer_name, std::string date)
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

						std::ofstream article("Artikli/" + code + ".txt", std::ios::app);
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