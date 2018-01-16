#include "Functions.h"
#include "Person.h"
#include "BillsReader.h"
#include "Report.h"
#include "AnalystFunctionals.h"
#include "Logo.h"

extern int application_exit;

void AnalystFunctionals()
{
	Person a;
	system("cls");
	int i = 3, p = 1, k = 1;//p-oznacava uspjesnu/neuspjesnu prijavu,i-broji neuspjele prijave
	while (i && k)
	{
		system("cls");
		logoS(); std::cout << std::endl << "PRIJAVA ZA ANALITICARA" << std::endl << std::endl;
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
				char t = '1';//t omogucava vracanje na pocetak profila
				while (t=='1')
				{
					k = 0;
					char option3;
					do
					{
						system("cls");
						logoS(); std::cout << std::endl << "PRISTUP KAO ANALITICARU OMOGUCEN!!!" << std::endl;
						std::cout << std::endl << "1. Pregled podataka za odredjenog kupca" << std::endl;
						std::cout << "2. Pregled podataka za odredjeni proizvod" << std::endl;
						std::cout << "3. Pregled ukupne prodaje za odredjeni mjesec" << std::endl;
						std::cout << std::endl << "Odaberi opciju: "; std::cin >> option3;
					} while (option3 != '1' && option3 != '2' && option3 != '3');
					if (option3 == '1')
					{
						buyerReport();
					}
					if (option3 == '2')
					{
						char option4;
						do
						{
							system("cls");
							logoS(); std::cout << std::endl << "ODABRALI STE OPCIJU PREGLED PODATAKA ZA ODREDJENI PROIZVOD" << std::endl;
							std::cout << std::endl << "1. Ukupni pregled podataka za odredjeni proizvod" << std::endl;
							std::cout << "2. Pregled podataka za odredjeni proizvod u vremenskom intervalu" << std::endl;
							std::cout << std::endl << "Odaberi opciju: "; std::cin >> option4;
						} while (option4 != '1' && option4 != '2');
						if (option4 == '1')
						{
							std::cout << "IVANAAA" << std::endl;
						}
						else if (option4 == '2')
						{
							std::string date1, date2, article;
							int p = 0;
							do {
								system("cls");
								logoS();
								std::cout << std::endl << "PREGLED ZA ODREDJEN VREMENSKI INTERVAL" << std::endl;
								std::cout << std::endl;
								std::cout << "Artikal: ";
								article = input();
								std::cout << std::endl;

								std::string path = "Artikli/" + article + ".txt";
								std::ifstream f(path.c_str());

								std::cout << "Datum od: ";
								std::cin >> date1;
								std::cout << "Datum do: ";
								std::cin >> date2;

								int num1, num2;
								num1 = parseDate(date1);
								num2 = parseDate(date2);

								if (checkDate(date1) && checkDate(date2) && num1 <= num2 && f)
								{
									articleReport(article, num1, num2);
									p = 1;
								}
								else if (!f)
								{
									std::cout << "Uneseni artikal se ne nalazi u evidenciji" << std::endl;
									std::cout << "Pritisnite enter za novi unos" << std::endl;
									getchar();
									getchar();
									system("cls");
								}
								else if (!checkDate(date1))
								{
									std::cout << "Prvi datum nije validan" << std::endl;
									std::cout << "Pritisnite enter za novi unos" << std::endl;
									getchar();
									getchar();
									system("cls");
								}
								else if (!checkDate(date2))
								{
									std::cout << "Drugi datum nije validan" << std::endl;
									std::cout << "Pritisnite enter za novi unos" << std::endl;
									getchar();
									getchar();
									system("cls");
								}
								else
								{
									std::cout << "Drugi datum se nalazi ispred prvog" << std::endl;
									std::cout << "Pritisnite enter za novi unos" << std::endl;
									getchar();
									getchar();
									system("cls");
								}
							} while (p != 1);



							getchar();
							getchar();
						}
					}
					if (option3 == '3')
					{
						monthSaldoReport();
					}
					do
					{
						std::cout << std::endl << "0. Odjavi se" << std::endl;
						std::cout << "1. Vrati se na pocetak profila" << std::endl;
						std::cout << "2. Izadji iz aplikacije" << std::endl;
						std::cout << std::endl << "Unesi opciju: "; std::cin >> t;
						if (t == '0') application_exit = 1;
						if (t == '2')
						{
							application_exit = 0;
							t = '0';
						}
					} while (t != '0' && t != '1' && t != '2');
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
	//dio koda koji oznacava kod neuspjele prijave koji podatak nije korektno unesen (p==2 za ID, p==3 za PIN)
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