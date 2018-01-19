#include "Format2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>





void trim(std::string &s)
{
   size_t p = s.find_first_not_of(" \t");//vraca poziciju prvog karaktera koji nije prazan prostor
   s.erase(0, p);//brisanje razmaka sve do pojave prvog karaktera koji nije bjelina
	
	 p = s.find_last_not_of(" \t");//vraca poziciju posljednjeg karaktera koji nije space
	if (std::string::npos != p)
			s.erase(p + 1);
}
void buyer_file_output(std::string buyer_name, std::string date, std::vector<Article>& vec, double total, double pdv, double turbo_total)
{
	std::ofstream  fp(buyer_name, std::ios::app);//otvaram teks. datoteku kupac,u append mode,da se ne brise postojeci sadrzaj prilikom sljedeceg upisivanja u datoteku
	
	std::string code, name; double amount, price, total1;//podaci karakteristicni za artikal

	fp << date <<"."<< std::endl;
	for (int i = 0; i < vec.size(); i++)//petlja koja vrsi upis clanova niza Artikala u datoteku
	{
		code = vec[i].getCode(); name = vec[i].getName(); amount = vec[i].getAmount(); price= vec[i].getPrice();
		total1 = amount*price;
		fp << name <<" "<< code << " " << amount << " " << price << " " <<total1 << std::endl;

	}
	fp << total << std::endl << pdv << std::endl << turbo_total << std::endl;
	fp << "---------------------------------------" << std::endl;
	fp.close();
}
void article_file_output(std::string file_name, std::string name, std::string date, Article& art)
{

	std::ofstream  fp(file_name, std::ios::app);//otvaram tekst. datoteku Artikal.txt,takodje u append mode,kao i kod kupca
	fp << name << std::endl << date <<"."<< std::endl;
	double amount, price, total;
	amount = art.getAmount(); price = art.getPrice();
	total = amount*price;
	
	fp << amount << " " << price << " " << total <<  std::endl;
	fp << "---------------------------------------" << std::endl;
	fp.close();



}



void format2Processing(std::string file_name)
{
	std::ifstream fp("Racuni/" + file_name);//ovo "Racuni/" omogucava da se txt fajl napravi u folderu Racuni
	std::string line, tmp,total_string,total_pdv_string,pdv_string,date;/*line je promjenljiva u kojoj se memorisu svi stringovi uzeti pri pozivu getline,a u tmp  svi stringovi koji nisu bitni
	total_string je string koji predstavlja ukupnu vrijednost(bez PDv-a),total_pdv_string je ukupno+pdv,ali u obliku stringa,pdv_string je pdv u obliku stringa**/
	double total, PDV, total_pdv;/*total je ukupna vrijednost bez pdv-a,ali kao decimalni zapis,odnosno double podatak,PDV je pdv kao double i total_pdv je ukupno+pdv(double podatak)*/
	bool flag = true;//logicka promjenljiva,stoji kao uslov u while petlji
	

	



	if (fp.is_open())//provjeravam da li je datoteka otvorena
	{

		
		
		for (int i = 0; i < 5; i++)
			std::getline(fp, line);//preskanje prvih pet linija u datoteci,da se moze uhvatiti ime kupca
		
		fp >> tmp;//hvatanje rijeci Kupac:
		std::getline(fp, line);//hvatanje stringa iza rijeci kupac

		
		std::string buyer_name = line;//buyer_name=ime kupca
		trim(buyer_name);

		std::getline(fp, line);
		std::getline(fp, line);
		
		
		std::vector<Article> vec;//inicijalizacija niza artikala,pomocni objekat za smijestanje ucitanih artikala
		std::string art_name, code, dash;//dash su crtice "-",takodje pomocna promjenljiva za hvatanje crtice
		
		double amount, price, total1;
		bool flag = true;
		
		
		while(flag==true)
		
		{
			
			Article art;//pomocna promjenljiva koja se stavlja u niz artikala
			std::getline(fp, line);
			fp >> art_name;
			
			if (art_name == "---------------------------------------")break;//osigurava izlazak iz while petlje,odnosno prestanak unosa artikala u niz
			fp >> code >> dash >> amount >> dash >> price >> dash >> total1;
			
			if ((amount*price) != total1)//validacija racuna-provjerava da li je dobro izracunata ukupna vrijednost artikle pojedinacno
			{
				fp.close();
				fp.open("Racuni/" + file_name, std::ios::in);
				
				
				std::ofstream file_error("Racuni_sa_greskom/" + file_name);
				while (getline(fp, line))//prebacivanje racuna sa greskom u poseban folder Racuni_sa_greskom
					file_error << line << std::endl;
				std::string error_name = "Error/" + file_name.erase(file_name.length() - 4, file_name.length());//pravljenje txt fajla u folderu Error
				error_name += "_error.txt";
				std::ofstream error; error.open(error_name);
				if (error.is_open())
					error << "Racun sadrzi gresku-ukupna vrijednost (kolicina*cijena) za jedan od artikala nije ispravna.";
				error.close();
				return;
			}
			


			
			
			
			




			
			art.setName(art_name); art.setCode(code);
			art.setAmount(amount); art.setPrice(price);
			vec.push_back(art);
		

			
			
		}   
		std::getline(fp, line);
		
		std::getline(fp, line);
		
		
		

		fp >> tmp >> total_string;//memorisanje promjenljive ukupna_vrijednost u obliku stringa
		
		
		std::getline(fp, line);
		fp >> tmp >> pdv_string;//memorisanje pdv-a u obliku stringa
		
		
		std::getline(fp, line);
		std::string tmp1, tmp2;//tmp,tmp1,tmp2 u ovom slucaju predstavljaju pomocnepromjenljive za memorisanje stringova ukupno,za,placanje
		fp >> tmp>>tmp1>>tmp2>>total_pdv_string;
		
		
		std::getline(fp, line);
		fp >> tmp >> date;//memorisanje datuma u string date
		
		std::replace(date.begin(), date.end(), '/', '.');//funkcija koja zamjenjuje svako pojavljivanje karaktera /,sa . kod datuma,ukoliko je datum oblika dan/mj/god
		
		
		
		total = stod(total_string);//funkcija koja prevodi string u double podataka
		
		PDV = stod(pdv_string);
		
		total_pdv = stod(total_pdv_string);
		
		double sum = 0,pdv1;//sum je pomocna promjenljiva za sabiranje ukupnih vrijednosti svih artikala u datoteci,pdv1 je takodje samo pomocna promjenljiva za poredjenje PDV-a(validacija racuna)


		for (int i = 0; i < vec.size(); i++)
		{
			sum += (vec[i].getAmount())*(vec[i].getPrice());//sabiranje ukupnih vrijednosti svih artikala
		}
		
		if (sum != total)//dio koda koji provjerava da li je dobro izracunata ukupna vrijednost(bez pdv-a)
		{
			fp.close();
			fp.open("Racuni/" + file_name, std::ios::in);
			std::ofstream file_error("Racuni_sa_greskom/" + file_name);
			while (getline(fp, line))
				file_error << line << std::endl;
			std::string error_name = "Error/" + file_name.erase(file_name.length() - 4, file_name.length());
			error_name += "_error.txt";
			std::ofstream error; error.open(error_name);
			if (error.is_open())
				error << "Racun sadrzi gresku-ukupna vrijednost(bez PDV-a) nije dobro izracunata.";
			error.close();
			return;

		}

		
		
		pdv1 = sum * 17 /100;//racuna pdv kao 17% ukupne cijene
		
		
		
		if (PDV != pdv1)//dio koda koji provjerava da li je PDV dobro izracunat

		{
			fp.close();
			fp.open("Racuni/" + file_name, std::ios::in);
			std::ofstream file_error("Racuni_sa_greskom/" + file_name);
			while (getline(fp, line))
				file_error << line << std::endl;
			std::string error_name = "Error/" + file_name.erase(file_name.length() - 4, file_name.length());
			error_name += "_error.txt";
			std::ofstream error; error.open(error_name);
			if (error.is_open())
				error << "Racun sadrzi gresku-PDV nije dobro izracunat.";
			error.close();
			return;

		}
		double total_plus_pdv = pdv1 + sum;
		
		
		if (total_pdv != total_plus_pdv)//dio koda koji provjerava da li je dobro izracunata ukupna vrijednost za placanje(ukupno+pdv)
		{
			fp.close();
			fp.open("Racuni/" + file_name, std::ios::in);
			std::ofstream file_error("Racuni_sa_greskom/" + file_name);
			while (getline(fp, line))
				file_error << line << std::endl;
			std::string error_name = "Error/" + file_name.erase(file_name.length() - 4, file_name.length());
			error_name += "_error.txt";
			std::ofstream error; error.open(error_name);
			if (error.is_open())
				error << "Racun sadrzi gresku-ukupna vrijednost za placanje(pdv+ukupno) nije dobro izracunata.";
			error.close();
			return;

		}
		std::string art_file, buyer_file;//art_file=ime txt fajla u kojem ce biti smjesteni podaci o artiklu,buyer_file= ime txt fajla u kjem ce biti smjesteni podaci o kupcu
		
		buyer_file = "Kupci/" + buyer_name + ".txt";//omogucava kreiranje txt fajla u folderu "Kupci/"
		
		buyer_file_output(buyer_file, date, vec, total, PDV, total_pdv);//poziv funkcije za upis podataka o kupcima u datoteku
		for (int i = 0; i < vec.size(); i++)
		{
			art_file = "Artikli/" + vec[i].getName()+ " " + vec[i].getCode() + ".txt";//omogucava kreiranje txt fajla u folderu "Artikli/"
			article_file_output(art_file, buyer_name, date, vec[i]);//poziv funkcije za upis podataka o artiklima u datoteku
		}
		

	   


		
		
		
		
		

		



		fp.close();





	}
	else std::cout << "Neuspjesno otvaranje datoteke." << std::endl;//ukoliko datoteka nije uspjesno otvorena,ispisuje se poruka
	std::ofstream processed_file("Obradjeni_racuni/" + file_name);//omogucava da se kreira txt fajl racuna koji je obradjen u folderu "Obradjeni_racuni/"
	std::ifstream old_file("Racuni/" + file_name);

	while (getline(old_file, line))
		processed_file << line << std::endl;//kopiranje sadrzaja iz racuna koji je upravo obradjen u txt fajl koji je formiran u folderu "Obradjeni_racuni/"
}