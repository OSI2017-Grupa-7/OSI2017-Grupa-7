#include "Format1.h"
#include "Format2.h"
#include <string>
#include <algorithm>
using std::string;

struct Artikal {
	string AArticle, ACode, AQuant, APrice,ATotal; //pomocna struktura,napravljena radi lakse formatiranog upisa
	
};

bool checkError(string& file) // funkcija za provjeru greski
{
	string tmp,billTotal, PDV, billTotalPDV,tmp2;
	int flag = 1,errflag=0; Artikal art;
	double kol, cjn, ukp,sum=0,sumR,sumPDV,sumUkup;
	std::ifstream fp("Racuni/" + file); //otvaranje fajla koji sadrzi racune
	string tmperr = file;
	string errorfilestring = "Error/" + tmperr.erase(tmperr.length() - 4, tmperr.length()) + "_error" + ".txt";
	std::getline(fp, tmp);
    std::getline(fp, tmp);
	std::getline(fp, tmp);
	std::getline(fp, tmp);
	std::getline(fp, tmp); // preskakanje linija u racunu,koje ne sadrze bitne informacije
	while (flag == 1) // ucitavanje artikala jedan po jedan
	{
		std::getline(fp, tmp);
		fp >> art.AArticle;
		if (art.AArticle == "---------------------------------------")break;
		fp >> art.ACode;
		fp >> tmp2;
		fp >> art.AQuant;
		fp >> tmp2;
		fp >> art.APrice;
		fp >> tmp2;
		fp >> art.ATotal;
		kol = std::stod(art.AQuant);
		cjn = std::stod(art.APrice);
		ukp = std::stod(art.ATotal);
		sum = sum + std::stod(art.ATotal);
		if (kol*cjn != ukp) //provjera prve greske
		{
			std::ofstream errortxt(errorfilestring, std::ios::app); // otvaranje fajla u koji se smjestaju informacije o greskama
			errortxt << "Racun sadrzi gresku-Kolicina*Cijena artikla nije dobro izracunata." << std::endl;
			errflag = 1;
		}
	}
	std::getline(fp, tmp);
	fp >> tmp;
	fp >> billTotal;
	sumR = std::stod(billTotal);
	if (sum != sumR) // provjera druge greske
	{
		std::ofstream errortxt(errorfilestring, std::ios::app); // otvaranje fajla u koji se smjestaju informacije o greskama
		errortxt << "Racun sadrzi gresku-ukupna vrijednost(bez PDV-a) nije dobro izracunata." << std::endl;
		errflag=1;
	}
	std::getline(fp, tmp);
	fp >> tmp;
	fp >> PDV;
	sumPDV = std::stod(PDV);
	if (sumPDV != sumR*0.17) // provjera trece greske
	{
		std::ofstream errortxt(errorfilestring, std::ios::app); // otvaranje fajla u koji se smjestaju informacije o greskama
		errortxt << "Racun sadrzi gresku-PDV nije dobro izracunat." << std::endl;
		errflag=1;
	}
	std::getline(fp, tmp);
	fp >> tmp;
	fp >> tmp;
	fp >> tmp;
	fp >> billTotalPDV;
	sumUkup = std::stod(billTotalPDV);
	if (sumUkup != sumR + sumPDV) // provjera cetvrte greske
	{
		std::ofstream errortxt(errorfilestring, std::ios::app); // otvaranje fajla u koji se smjestaju informacije o greskama
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
	string tmp,BBuyer,billTotal,PDV,billTotalPDV,BDate,tmp2,tmp3,stringart,stringkup;
	Artikal art;
	int flag = 1,datec=0;
	if (checkError(file) == true) return; // provjera postojanja greske u racunu
	fp >> tmp; 
	std::getline(fp, BBuyer); // uzimanje imena kupca
	trim(BBuyer); //  brisanje viska prostora oko imena i prezimena
	fp >> tmp;
	fp >> BDate;
	std::replace(BDate.begin(), BDate.end(), '/', '.'); //promjena svakog pojavljivanja / u . unutar datuma
	std::getline(fp, tmp);
	std::getline(fp, tmp);
	std::getline(fp, tmp);
	std::getline(fp, tmp); //preskakanje nebitnih linija
	
	while(flag==1) // petlja unutar koje se ucitavaju podaci
	{
		std::getline(fp, tmp);
		fp >> art.AArticle;
		if (art.AArticle == "---------------------------------------")break; // uslov koji odredjuje da li postoji jos artikala u fajlu
		fp >> art.ACode;
		fp >> tmp2;
		fp >> art.AQuant;
		fp >> tmp2;
		fp >> art.APrice;
		fp >> tmp2;
		fp >> art.ATotal;
		stringart = "Artikli/" + art.AArticle + " " + art.ACode + ".txt"; //pronalazak imena fajla u kome se cuvaju podaci za dati artikal
		stringkup = "Kupci/"+ BBuyer +".txt"; //pronalazak imena fajla u kome se cuvaju podaci za datog kupca
	   std::ofstream fileart(stringart,std::ios::app), filekup(stringkup,std::ios::app); //otvaranje fajlova u append modu
		fileart << BBuyer << std::endl;
		fileart << BDate << std::endl;
		fileart << art.AQuant << " " << art.APrice << " " << art.ATotal << std::endl; //upis podataka u file vezan za artikal
		fileart << "---------------------------------------" << std::endl;
		if (datec == 0) { filekup << BDate <<"."<< std::endl; datec++; } // provjera koja osigura da ce se datum samo jednom unijeti u fajl za sve artikle kupljenje u istom danu
		filekup <<art.AArticle<< " " << art.ACode << " " << art.AQuant << " " << art.APrice << " " << art.ATotal << std::endl; //unos podataka u fajl kupca
	}
	std::getline(fp, tmp);
	fp >> tmp;
	fp >> billTotal;
	std::getline(fp, tmp);
	fp >> tmp;
	fp >> PDV;
	std::getline(fp, tmp);
	fp >> tmp;
	fp >> tmp;
	fp >> tmp;
	fp >> billTotalPDV; //ucitavanje zadnjih podataka u fajlu,ukupne vrijednosti,PDVa i ukupne vrijednosti sa PDV-om
	std::ofstream filekup(stringkup, std::ios::app);
	filekup << billTotal << std::endl;
	filekup << PDV << std::endl;
	filekup << billTotalPDV << std::endl;
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


