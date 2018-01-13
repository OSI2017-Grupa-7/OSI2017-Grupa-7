#include "Format1.h"
#include "Format2.h"
#include <string>
#include <algorithm>
using std::string;

struct Artikal {
	string proizvod, sifra, kolicina, cijena,ukupno;
	
};

bool checkError(string& file)
{
	string pom,racUkupno, PDV, ukupPDV,pom2;
	int flag = 1,errflag=0; Artikal art;
	double kol, cjn, ukp,sum=0,sumR,sumPDV,sumUkup;
	std::ifstream fp("Racuni/" + file);
	std::getline(fp, pom);
    std::getline(fp, pom);
	std::getline(fp, pom);
	std::getline(fp, pom);
	std::getline(fp, pom);
	while (flag == 1)
	{
		std::getline(fp, pom);
		fp >> art.proizvod;
		if (art.proizvod == "---------------------------------------")break;
		fp >> art.sifra;
		fp >> pom2;
		fp >> art.kolicina;
		fp >> pom2;
		fp >> art.cijena;
		fp >> pom2;
		fp >> art.ukupno;
		kol = std::stod(art.kolicina);
		cjn = std::stod(art.cijena);
		ukp = std::stod(art.ukupno);
		sum = sum + std::stod(art.ukupno);
		if (kol*cjn != ukp) 
		{
			std::cout << "Racun sadrzi gresku-kolicina*cijena artikla nije dobro izracunata." << std::endl;
			errflag = 1;
		}
	}
	std::getline(fp, pom);
	fp >> pom;
	fp >> racUkupno;
	sumR = std::stod(racUkupno);
	if (sum != sumR)
	{
		std::cout << "Racun sadrzi gresku-ukupna vrijednost(bez PDV-a) nije dobro izracunata." << std::endl;
		errflag=1;
	}
	std::getline(fp, pom);
	fp >> pom;
	fp >> PDV;
	sumPDV = std::stod(PDV);
	if (sumPDV != sumR*0.17)
	{
		std::cout << "Racun sadrzi gresku-PDV nije dobro izracunat." << std::endl;
		errflag=1;
	}
	std::getline(fp, pom);
	fp >> pom;
	fp >> pom;
	fp >> pom;
	fp >> ukupPDV;
	sumUkup = std::stod(ukupPDV);
	if (sumUkup != sumR + sumPDV)
	{
		std::cout << "Racun sadrzi gresku-ukupna vrijednost za placanje(pdv+ukupno) nije dobro izracunata." << std::endl;
		errflag=1;
	}
    fp.seekg(0, fp.beg);
	if (errflag==0) return false;
	
	std::ofstream error("Error/" + file);
	string copy;
	while (std::getline(fp, copy))
	{
		error << copy;
		error << std::endl;
	}
	fp.seekg(0, fp.beg);
	return true;
}

void format1(std::string& file)
{
	std::ifstream fp("Racuni/" + file);
	string pom,Kupac,racUkupno,PDV,ukupPDV,datum,pom2,pom3,stringart,stringkup;
	Artikal art;
	int flag = 1,datec=0;
	if (checkError(file) == true) return;
	fp >> pom;
	std::getline(fp, Kupac);
	trim(Kupac);
	fp >> pom;
	fp >> datum;
	std::replace(datum.begin(), datum.end(), '/', '.');
	std::getline(fp, pom);
	std::getline(fp, pom);
	std::getline(fp, pom);
	std::getline(fp, pom);
	
	while(flag==1)
	{
		std::getline(fp, pom);
		fp >> art.proizvod;
		if (art.proizvod == "---------------------------------------")break;
		fp >> art.sifra;
		fp >> pom2;
		fp >> art.kolicina;
		fp >> pom2;
		fp >> art.cijena;
		fp >> pom2;
		fp >> art.ukupno;
		stringart = "Artikli/" + art.proizvod + " " + art.sifra + ".txt";
		stringkup = "Kupci/"+ Kupac +".txt";
	   std::ofstream fileart(stringart,std::ios::app), filekup(stringkup,std::ios::app);
		fileart << Kupac << std::endl;
		fileart << datum << std::endl;
		fileart << art.kolicina << " " << art.cijena << " " << art.ukupno << std::endl;
		fileart << "---------------------------------------" << std::endl;
		if (datec == 0) { filekup << datum << std::endl; datec++; }
		filekup <<art.proizvod<< " " << art.sifra << " " << art.kolicina << " " << art.cijena << " " << art.ukupno << std::endl;
	}
	std::getline(fp, pom);
	fp >> pom;
	fp >> racUkupno;
	std::getline(fp, pom);
	fp >> pom;
	fp >> PDV;
	std::getline(fp, pom);
	fp >> pom;
	fp >> pom;
	fp >> pom;
	fp >> ukupPDV;
	std::ofstream filekup(stringkup, std::ios::app);
	filekup << racUkupno << std::endl;
	filekup << PDV << std::endl;
	filekup << ukupPDV << std::endl;
	filekup << "---------------------------------------" << std::endl;
    fp.seekg(0, fp.beg);
	std::ofstream done("Obradjeni_racuni/" + file);
	string copy;
	while (std::getline(fp, copy)) 
	{
		done << copy;
		done << std::endl;
	}

	
}


