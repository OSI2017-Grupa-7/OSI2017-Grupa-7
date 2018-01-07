#include "Format1.h"
#include <string>
using std::string;

struct Artikal {
	string proizvod, sifra, kolicina, cijena,ukupno;
	
};

bool checkError(string& file)
{
	string pom,racUkupno, PDV, ukupPDV,pom2;
	int flag = 1; Artikal art;
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
		if (kol*cjn != ukp) return true;
	}
	std::getline(fp, pom);
	fp >> pom;
	fp >> racUkupno;
	sumR = std::stod(racUkupno);
	if (sum != sumR) return true;
	std::getline(fp, pom);
	fp >> pom;
	fp >> PDV;
	sumPDV = std::stod(PDV);
	if (sumPDV!=sumR*0.17) return true;
	std::getline(fp, pom);
	fp >> pom;
	fp >> pom;
	fp >> pom;
	fp >> ukupPDV;
	sumUkup = std::stod(ukupPDV);
	if (sumUkup!=sumR+sumPDV) return true;
	
    fp.seekg(0, fp.beg);
	return false;
}

void format1(std::string& file)
{
	std::ifstream fp("Racuni/" + file);
	string pom,kupacIme,kupacPrez,racUkupno,PDV,ukupPDV,datum,pom2,pom3,stringart,stringkup;
	Artikal art;
	int flag = 1,datec=0;
	if (checkError(file) == true) return;
	fp >> pom;
	fp >> kupacIme;
	fp >> kupacPrez;
	std::getline(fp, pom);
	fp >> pom;
	fp >> datum;
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
		stringart = "Artikli/" + art.sifra + ".txt";
		stringkup = "Kupci/"+kupacIme + kupacPrez+".txt";
	   std::ofstream fileart(stringart,std::ios::app), filekup(stringkup,std::ios::app);
		fileart << kupacIme+kupacPrez << std::endl;
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


