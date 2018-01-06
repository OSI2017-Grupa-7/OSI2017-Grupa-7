#include "Format2.h"
#include <iostream>
#include <fstream>






void buyer_file_output(std::string file_name, std::string date, std::vector<Article>& vec, double total, double pdv, double turbo_total)
{
	std::ofstream fp; fp.open(file_name);
	std::string sifra, naziv; double kol, cijena, uk;

	fp << date << std::endl;
	for (int i = 0; i < vec.size(); i++)
	{
		sifra = vec[i].getSifra(); naziv = vec[i].getNaziv(); kol = vec[i].getKolicina(); cijena = vec[i].getCijena();
		uk = kol*cijena;
		fp << sifra << " " << naziv << " " << kol << " " << cijena << " " << uk << std::endl;

	}
	fp << total << std::endl << pdv << std::endl << turbo_total << std::endl;
	fp << "---------------------------------------" << std::endl;
	fp.close();
}
void article_file_output(std::string file_name, std::string name, std::string date, Article& art, double pdv)
{

	std::ofstream fp; fp.open(file_name);
	fp << name << std::endl << date << std::endl;
	double kol, cijena, uk, uk_pdv;
	kol = art.getKolicina(); cijena = art.getCijena();
	uk = kol*cijena;
	uk_pdv = uk + pdv;
	fp << kol << " " << cijena << " " << uk << " " << pdv << " " << uk_pdv << std::endl;
	fp << "---------------------------------------" << std::endl;
	fp.close();



}



void format2Processing(std::string file_name)
{
	std::ifstream fp("Racuni/" + file_name);
	std::string line, pom, name, buyer_file;

	pom = "Kupac:";



	if (fp.is_open())
	{
		std::cout << " Otvorena je datoteka pod nazivom  " << file_name;
		for (int i = 0; i < 6; i++)
			std::getline(fp, line);//hvatam prvih 5 linija koda ukljucujuci i onu gdje je kupac:

		for (int i = pom.length() + 1; i < line.length(); i++)//i pocinje nakon rijeci kupac:,da odmah preskocim to i hvatam ime
		{
			int j = 0;
			if (line[i] != ' ')
				name[j++] = line[i];
		}
		for (int i = 0; i < 3; i++)
			std::getline(fp, line);
		std::vector<Article> vec;
		std::string art_name, code, dash;
		dash = "-";
		double measure, price, total;
		fp >> art_name >> code >> dash >> measure >> dash >> price >> dash >> total;
		while (art_name != "---------------------------------------")
		{
			Article art;



			if ((measure*price) != total)
			{
				fp.close();
				std::string error_name = "Error/" + file_name + "_error" + ".txt";
				std::ofstream error; error.open(error_name);
				if (error.is_open())
					error << "Racun sadrzi gresku-ukupna vrijednost (kolicina*cijena) nije ispravna";
				error.close();
				return;
			}
			art.setNaziv(art_name); art.setSifra(code);
			art.setKolicina(measure); art.setCijena(price);
			vec.push_back(art);
			fp >> art_name >> code >> dash >> measure >> dash >> price >> dash >> total;
		}

		double turbo_total = 0, turbo_total_pdv = 0, pdv;
		std::string date, pdv_s;
		for (int i = 0; i < 3; i++)
			std::getline(fp, line);
		std::string pom1 = "PDV:", pom2 = "Datum:";
		for (int i = pom1.length() + 1; i < line.length(); i++)
		{
			int j = 0;
			if (line[i] != ' ')
				pdv_s[j++] = line[i];
		}
		pdv = stod(pdv_s);//string u double
		for (int i = 0; i < vec.size(); i++)
		{
			turbo_total += vec[i].getKolicina()*vec[i].getCijena();
		}
		turbo_total_pdv = turbo_total + pdv;
		std::getline(fp, line);
		std::getline(fp, line);


		for (int i = pom2.length() + 1; i < line.length(); i++)
		{
			int j = 0;
			if (line[i] != ' ')
				date[j++] = line[i];
		}
		buyer_file = "Kupci/" + name + ".txt";
		buyer_file_output(buyer_file, date, vec, turbo_total, pdv, turbo_total_pdv);
		for (int i = 0; i < vec.size(); i++)
		{
			std::string sifra = vec[i].getSifra(), article_file;
			article_file = "Artikli/" + sifra + ".txt";
			article_file_output(article_file, name, date, vec[i], pdv);

		}

		fp.close();





	}
	else std::cout << "Neuspjesno otvaranje datoteke." << std::endl;
	std::ofstream processed_file("Obradjeni_racuni/" + file_name);
	std::ifstream old_file("Racuni/" + file_name);

	while (getline(old_file, line))
		processed_file << line << std::endl;
}