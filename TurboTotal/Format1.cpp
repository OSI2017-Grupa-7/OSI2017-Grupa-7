#include "Format1.h"
#include "Format2.h"
#include <string>
#include <algorithm>
using std::string;

struct Artikal {
	string proizvod, sifra, kolicina, cijena,ukupno; //pomocna struktura,napravljena radi lakse formatiranog upisa
	
};

bool checkError(string& file) // funkcija za provjeru greski
{
	string pom,racUkupno, PDV, ukupPDV,pom2;
	int flag = 1,errflag=0; Artikal art;
	double kol, cjn, ukp,sum=0,sumR,sumPDV,sumUkup;
	std::ifstream fp("Racuni/" + file); //otvaranje fajla koji sadrzi racune
	std::ofstream errortxt("Error/" + file); // otvaranje fajla u koji se smjestaju informacije o greskama
	std::getline(fp, pom);
    std::getline(fp, pom);
	std::getline(fp, pom);
	std::getline(fp, pom);
	std::getline(fp, pom); // preskakanje linija u racunu,koje ne sadrze bitne informacije
	while (flag == 1) // ucitavanje artikala jedan po jedan
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
		if (kol*cjn != ukp) //provjera prve greske
		{
			errortxt << "Racun sadrzi gresku-kolicina*cijena artikla nije dobro izracunata." << std::endl;
			errflag = 1;
		}
	}
	std::getline(fp, pom);
	fp >> pom;
	fp >> racUkupno;
	sumR = std::stod(racUkupno);
	if (sum != sumR) // provjera druge greske
	{
		errortxt << "Racun sadrzi gresku-ukupna vrijednost(bez PDV-a) nije dobro izracunata." << std::endl;
		errflag=1;
	}
	std::getline(fp, pom);
	fp >> pom;
	fp >> PDV;
	sumPDV = std::stod(PDV);
	if (sumPDV != sumR*0.17) // provjera trece greske
	{
		errortxt << "Racun sadrzi gresku-PDV nije dobro izracunat." << std::endl;
		errflag=1;
	}
	std::getline(fp, pom);
	fp >> pom;
	fp >> pom;
	fp >> pom;
	fp >> ukupPDV;
	sumUkup = std::stod(ukupPDV);
	if (sumUkup != sumR + sumPDV) // provjera cetvrte greske
	{
		errortxt << "Racun sadrzi gresku-ukupna vrijednost za placanje(pdv+ukupno) nije dobro izracunata." << std::endl;
		errflag=1;
	}
    fp.seekg(0, fp.beg);
	if (errflag==0) return false;
	
	std::ofstream error("Racuni_sa_greskom/" + file); // otvaranje datoteke za smjestanje racuna sa greskom
	string copy;
	while (std::getline(fp, copy))  //upis kopije racuna u folder sa ostalim koji imaju gresku
	{
		error << copy;
		error << std::endl;
	}
	fp.seekg(0, fp.beg); //vracanje na sam pocetak datoteke
	return true;
}

void format1(std::string& file)
{
	std::ifstream fp("Racuni/" + file); // otvaranje fajla koji sadrzi informacije
	string pom,Kupac,racUkupno,PDV,ukupPDV,datum,pom2,pom3,stringart,stringkup;
	Artikal art;
	int flag = 1,datec=0;
	if (checkError(file) == true) return; // provjera postojanja greske u racunu
	fp >> pom; 
	std::getline(fp, Kupac); // uzimanje imena kupca
	trim(Kupac); //  brisanje viska prostora oko imena i prezimena
	fp >> pom;
	fp >> datum;
	std::replace(datum.begin(), datum.end(), '/', '.'); //promjena svakog pojavljivanja / u . unutar datuma
	std::getline(fp, pom);
	std::getline(fp, pom);
	std::getline(fp, pom);
	std::getline(fp, pom); //preskakanje nebitnih linija
	
	while(flag==1) // petlja unutar koje se ucitavaju podaci
	{
		std::getline(fp, pom);
		fp >> art.proizvod;
		if (art.proizvod == "---------------------------------------")break; // uslov koji odredjuje da li postoji jos artikala u fajlu
		fp >> art.sifra;
		fp >> pom2;
		fp >> art.kolicina;
		fp >> pom2;
		fp >> art.cijena;
		fp >> pom2;
		fp >> art.ukupno;
		stringart = "Artikli/" + art.proizvod + " " + art.sifra + ".txt"; //pronalazak imena fajla u kome se cuvaju podaci za dati artikal
		stringkup = "Kupci/"+ Kupac +".txt"; //pronalazak imena fajla u kome se cuvaju podaci za datog kupca
	   std::ofstream fileart(stringart,std::ios::app), filekup(stringkup,std::ios::app); //otvaranje fajlova u append modu
		fileart << Kupac << std::endl;
		fileart << datum << std::endl;
		fileart << art.kolicina << " " << art.cijena << " " << art.ukupno << std::endl; //upis podataka u file vezan za artikal
		fileart << "---------------------------------------" << std::endl;
		if (datec == 0) { filekup << datum <<"."<< std::endl; datec++; } // provjera koja osigura da ce se datum samo jednom unijeti u fajl za sve artikle kupljenje u istom danu
		filekup <<art.proizvod<< " " << art.sifra << " " << art.kolicina << " " << art.cijena << " " << art.ukupno << std::endl; //unos podataka u fajl kupca
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
	fp >> ukupPDV; //ucitavanje zadnjih podataka u fajlu,ukupne vrijednosti,PDVa i ukupne vrijednosti sa PDV-om
	std::ofstream filekup(stringkup, std::ios::app);
	filekup << racUkupno << std::endl;
	filekup << PDV << std::endl;
	filekup << ukupPDV << std::endl;
	filekup << "---------------------------------------" << std::endl; //upis podataka u fajl za kupca
    fp.seekg(0, fp.beg); //vracanje na pocetak datoteke
	std::ofstream done("Obradjeni_racuni/" + file); //pravljenje kopije racuna u folderu za obradjene racune
	string copy;
	while (std::getline(fp, copy)) 
	{
		done << copy;
		done << std::endl;
	}

	
}


