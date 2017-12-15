#include "Functions.h"
#include "Person.h"
#include "BillsReader.h"
#include "Report.h"
#include "AnalystFunctionals.h"

extern int kraj;

void AnalystFunctionals()
{
	Person a;
	system("cls");
	int i = 3, p = 1, k = 1;
	while (i && k)
	{
		system("cls");
		std::cout << "PRIJAVA ZA ANALITICARA" << std::endl << std::endl;
		a.readPersonForLogin();
		p = checkForAnalyst(a.getID(), a.getPIN());
		if (p == 5)
		{
			k = 0;
			system("cls");
			std::cout << "NEMATE PRAVO PRISTUPA SISTEMU, KONTAKTIRAJTE ADMINISTRATORA!!";
			getchar();
			getchar();
		}
		else
		{
			if (p == 1)
			{
				billsReading();//FUNKCIJA ZA CITANJE, OBRADU, SKLADISTENJE RACUNA
				int t = 1;
				while (t)
				{
					k = 0;
					short option3;
					do
					{
						system("cls");
						std::cout << "PRISTUP KAO ANALITICARU OMOGUCEN!!!" << std::endl;
						std::cout << std::endl << "1. Pregled podataka za odredjenog kupca" << std::endl;
						std::cout << "2. Pregled podataka za odredjeni proizvod" << std::endl;
						std::cout << "3. Pregled ukupne prodaje za odredjeni mjesec" << std::endl;
						std::cout << std::endl << "Odaberi opciju: "; std::cin >> option3;
					} while (option3 != 1 && option3 != 2 && option3 != 3);
					if (option3 == 1)
					{
						buyerReport();
					}
					if (option3 == 2)
					{
						productReport();
					}
					if (option3 == 3)
					{
						monthSaldoReport();
					}
					do
					{
						std::cout << std::endl << "0. Odjavi se" << std::endl;
						std::cout << "1. Vrati se na pocetak profila" << std::endl;
						std::cout << "2. Izadji iz aplikacije" << std::endl;
						std::cout << std::endl << "Unesi opciju: "; std::cin >> t;
						if (t == 0) kraj = 1;
						if (t == 2)
						{
							kraj = 0;
							t = 0;
						}
					} while (t != 0 && t != 1 && t != 2);
				}
			}
			else
			{
				std::cout << std::endl << "ID ili sifra nisu korektno uneseni. Broj preostalih pokusaja: " << --i << " (pritisni 'Enter' za sledeci pokusaj)";
				getchar();
				getchar();
			}

		}
	}
	if (!i && (p == 2 || p == 3))
	{
		if (p == 2)
		{
			std::string pom = a.getID();
			char name[15], surname[15], ID[15], PIN[15], maliciozan[15];
			FILE* myfile;
			myfile = fopen("RegistrovaniAnaliticari.txt", "r");
			std::vector <Person> v;
			Person b;
			while (fscanf(myfile, "%15s %15s %10s %10s %15s\n", name, surname, ID, PIN, maliciozan) == 5)
			{
				std::string nname(name); b.setName(nname);
				std::string ssurname(surname); b.setSurname(ssurname);
				std::string IID(ID); b.setID(IID);
				std::string PPIN(PIN); b.setPIN(PPIN);
				std::string mmaliciozan(maliciozan); b.setMalicious(mmaliciozan);
				v.push_back(b);
			}
			fclose(myfile);
			for (int i = 0; i < v.size(); i++)
			{
				if (v[i].getID() == pom)
				{
					if (maliciousAnalyst(v[i]))
					{
						v[i].getMalicious() = "onemogucen";
						std::ofstream f;
						f.open("MaliciozniAnaliticari.txt", std::ios::app);
						f << std::setw(15) << std::left << v[i].getName() << std::setw(15) << std::left << v[i].getSurname() << std::setw(10) << std::left << v[i].getID() << std::setw(10) << std::left << v[i].getPIN() << std::setw(10) << std::left << v[i].getMalicious() << std::endl;
						f.close();
					}
				}
			}
			std::ofstream file;
			file.open("RegistrovaniAnaliticari.txt");
			for (int i = 0; i < v.size(); i++)
				file << std::setw(15) << std::left << v[i].getName() << std::setw(15) << std::left << v[i].getSurname() << std::setw(10) << std::left << v[i].getID() << std::setw(10) << std::left << v[i].getPIN() << std::setw(10) << std::left << v[i].getMalicious() << std::endl;
			file.close();
		}
		if (p == 3)
		{
			std::string pom = a.getPIN();
			char name[15], surname[15], ID[15], PIN[15], maliciozan[15];
			FILE* myfile;
			myfile = fopen("RegistrovaniAnaliticari.txt", "r");
			std::vector <Person> v;
			Person b;
			while (fscanf(myfile, "%15s %15s %10s %10s %15s\n", name, surname, ID, PIN, maliciozan) == 5)
			{
				std::string nname(name); b.setName(nname);
				std::string ssurname(surname); b.setSurname(ssurname);
				std::string IID(ID); b.setID(IID);
				std::string PPIN(PIN); b.setPIN(PPIN);
				std::string mmaliciozan(maliciozan); b.setMalicious(mmaliciozan);
				v.push_back(b);
			}
			fclose(myfile);
			for (int i = 0; i < v.size(); i++)
			{
				if (v[i].getID() == pom)
				{
					if (maliciousAnalyst(v[i]))
					{
						v[i].getMalicious() = "onemogucen";
						std::ofstream f;
						f.open("MaliciozniAnaliticari.txt", std::ios::app);
						f << std::setw(15) << std::left << v[i].getName() << std::setw(15) << std::left << v[i].getSurname() << std::setw(10) << std::left << v[i].getID() << std::setw(10) << std::left << v[i].getPIN() << std::setw(10) << std::left << v[i].getMalicious() << std::endl;
						f.close();
					}
				}
			}
			std::ofstream file;
			file.open("RegistrovaniAnaliticari.txt");
			for (int i = 0; i < v.size(); i++)
				file << std::setw(15) << std::left << v[i].getName() << std::setw(15) << std::left << v[i].getSurname() << std::setw(10) << std::left << v[i].getID() << std::setw(10) << std::left << v[i].getPIN() << std::setw(10) << std::left << v[i].getMalicious() << std::endl;
			file.close();
		}
		system("cls");
		std::cout << "Pogresno ste unijeli podatke za prijavu 3x uzastopno." << std::endl;
		std::cout << std::endl << "Da biste opet imali pristup sistemu, kontaktirajte administratora." << std::endl;
	}
	getchar();
}