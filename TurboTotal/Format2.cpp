#include "Format2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>





void buyer_file_output(std::string buyer_name, std::string date, std::vector<Article>& vec, double total, double pdv, double turbo_total)
{
	std::ofstream  fp(buyer_name, std::ios::app);
	
	std::string sifra, naziv; double kol, cijena, uk;

	fp << date << std::endl;
	for (int i = 0; i < vec.size(); i++)
	{
		sifra = vec[i].getSifra(); naziv = vec[i].getNaziv(); kol = vec[i].getKolicina(); cijena = vec[i].getCijena();
		uk = kol*cijena;
		fp << naziv << sifra << " " << kol << " " << cijena << " " << uk << std::endl;

	}
	fp << total << std::endl << pdv << std::endl << turbo_total << std::endl;
	fp << "---------------------------------------" << std::endl;
	fp.close();
}
void article_file_output(std::string file_name, std::string name, std::string date, Article& art)
{

	std::ofstream  fp(file_name, std::ios::app);
	fp << name << std::endl << date << std::endl;
	double kol, cijena, uk;
	kol = art.getKolicina(); cijena = art.getCijena();
	uk = kol*cijena;
	
	fp << kol << " " << cijena << " " << uk <<  std::endl;
	fp << "---------------------------------------" << std::endl;
	fp.close();



}



void format2Processing(std::string file_name)
{
	std::ifstream fp("Racuni/" + file_name);
	std::string line, pom, name,surname, buyer_file,uk,pdv,uk_pdv,date;
	double ukupno, PDV, ukupno_pdv;
	bool flag = true;
	

	



	if (fp.is_open())
	{

		
		
		for (int i = 0; i < 5; i++)
			std::getline(fp, line);
		
		fp >> pom >> name>> surname;
		std::getline(fp, line);
		std::string buyer_name = name + surname;
		
		std::getline(fp, line);
		std::getline(fp, line);
		
		
		std::vector<Article> vec;
		std::string art_name, code, dash;
		
		double measure, price, total;
		bool flag = true;
		
		
		while(flag==true)
		{
			
			Article art;
			std::getline(fp, pom);
			fp >> art_name;
			if (art_name == "---------------------------------------")break;
			fp >> code >> dash >> measure >> dash >> price >> dash >> total;
			
			if ((measure*price) != total)
			{
				fp.close();
				std::string error_name = "Error/" + file_name + "_error" + ".txt";
				std::ofstream error; error.open(error_name);
				if (error.is_open())
					error << "Racun sadrzi gresku-ukupna vrijednost (kolicina*cijena) nije ispravna.";
				error.close();
				return;
			}

			
			
			
			




			
			art.setNaziv(art_name); art.setSifra(code);
			art.setKolicina(measure); art.setCijena(price);
			vec.push_back(art);
			
			
			
		} 
		std::getline(fp, line);
		fp >> pom >> uk;
		
		std::getline(fp, line);
		fp >> pom >> pdv;
		
		std::getline(fp, line);
		std::string pom1, pom2;
		fp >> pom>>pom1>>pom2>>uk_pdv;
		
		std::getline(fp, line);
		fp >> pom >> date;
		std::replace(date.begin(), date.end(), '/', '.');
		
		
		
		ukupno = stod(uk);
		PDV = stod(pdv);
		ukupno_pdv = stod(uk_pdv);
		double sum = 0,pdv1;


		for (int i = 0; i < vec.size(); i++)
		{
			sum += vec[i].getKolicina()*vec[i].getCijena();
		}
		
		if (sum != ukupno)
		{
			fp.close();
			std::string error_name = "Error/" + file_name + "_error" + ".txt";
			std::ofstream error; error.open(error_name);
			if (error.is_open())
				error << "Racun sadrzi gresku-ukupna vrijednost(bez PDV-a) nije dobro izracunata.";
			error.close();
			return;

		}

		
		
		pdv1 = 0.17 * ukupno;
		
		
		if (pdv1 != PDV)
		{
			fp.close();
			std::string error_name = "Error/" + file_name + "_error" + ".txt";
			std::ofstream error; error.open(error_name);
			if (error.is_open())
				error << "Racun sadrzi gresku-PDV nije dobro izracunat.";
			error.close();
			return;

		}
		
		
		if (ukupno_pdv != (PDV + ukupno))
		{
			fp.close();
			std::string error_name = "Error/" + file_name + "_error" + ".txt";
			std::ofstream error; error.open(error_name);
			if (error.is_open())
				error << "Racun sadrzi gresku-ukupna vrijednost za placanje(pdv+ukupno) nije dobro izracunata.";
			error.close();
			return;

		}
		std::string art_file, buyer_file;
		
		buyer_file = "Kupci/" + buyer_name + ".txt";
		
		buyer_file_output(buyer_file, date, vec, ukupno, PDV, ukupno_pdv);
		for (int i = 0; i < vec.size(); i++)
		{
			art_file = "Artikli/" + vec[i].getSifra() + ".txt";
			article_file_output(art_file, buyer_name, date, vec[i]);
		}
		

	   


		
		
		
		
		

		



		fp.close();





	}
	else std::cout << "Neuspjesno otvaranje datoteke." << std::endl;
	std::ofstream processed_file("Obradjeni_racuni/" + file_name);
	std::ifstream old_file("Racuni/" + file_name);

	while (getline(old_file, line))
		processed_file << line << std::endl;
}