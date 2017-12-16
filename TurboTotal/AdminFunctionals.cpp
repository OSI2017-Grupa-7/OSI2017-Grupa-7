#include "AdminFunctionals.h"
#include "Functions.h"
#include "Logo.h"
extern int kraj;
void AdminFunctionals()
{
	Person a;
	int i = 3, k = 1, p;
	while (i && k)
	{
		system("cls");
		logoS();  std::cout << std::endl << std::endl << "PRIJAVA ZA ADMINISTRATORA" << std::endl << std::endl;
		a.readPersonForLogin();
		p = checkForAdmin(a.getID(), a.getPIN());
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
				char t = '1';
				while (t == '1')
				{
					k = 0;
					char option1;
					if (p)
					{
						do
						{
							system("cls");
							std::cout << "Uspjesno ste prijavljeni kao administrator!!" << std::endl;
							std::cout << std::endl << "1. Registruj novog korisnika" << std::endl;
							std::cout << "2. Ispis korisnika" << std::endl;
							std::cout << "3. Obrisi korisnika" << std::endl;
							std::cout << "4. Omoguci pristup korisniku" << std::endl;
							std::cout << std::endl << "Odaberi opciju: "; std::cin >> option1;
						} while (option1 != '1' && option1 != '2' && option1 != '3' && option1 != '4');
						/////////////////////////////////////////////////registracija korisnika
						if (option1 == '1')
						{
							char user;
							do
							{
								system("cls");
								std::cout << "REGISTRACIJA KORISNIKA" << std::endl;
								std::cout << std::endl << "Odaberi korisnicku klasu: " << std::endl;
								std::cout << std::endl << "1. Administrator" << std::endl;
								std::cout << "2. Analiticar" << std::endl;
								std::cout << std::endl << "Odaberi opciju: "; std::cin >> user;
							} while (user != '1' && user != '2');
							system("cls");
							if (user == '1')
							{
								char isCorrect = '2';
								Person a;
								int w;
								while (isCorrect == '2')
								{
									int IDlength = 0;
									do {
										system("cls");
										std::cout << "TURBO TOTAL 2000" << std::endl;
										std::cout << std::endl << "REGISTRACIJA NOVOG ADMINISTRATORA" << std::endl;
										std::cout << std::endl;
										IDlength = a.readPerson();
									} while (IDlength == 0);
									w = isThereAdmin(a);
									do
									{
										system("cls");
										std::cout << "Podaci koje ste unijeli: " << std::endl << std::endl;
										a.printPerson();
										if (w)
										{
											char y;
											do
											{
												system("cls");
												std::cout << "Podaci koje ste unijeli: " << std::endl << std::endl;
												a.printPerson();
												std::cout << std::endl << "Greska! Vec postoji administrator sa takvim podacima." << std::endl;
												std::cout << std::endl << "Da li zelite ponovo pokusati registrovati novog administratora?" << std::endl;
												std::cout << "1. Da" << std::endl;
												std::cout << "2. Ne" << std::endl;
												std::cout << std::endl << "Unesi opciju: "; std::cin >> y;
											} while (y != '1' && y != '2');
											if (y == '1')
											{
												isCorrect = '2';
											}
											if (y == '2')
											{
												isCorrect = '1';
											}
										}
										else
										{
											std::cout << std::endl << "Da li su ovo podaci koje ste htjeli unijeti?" << std::endl;
											std::cout << std::endl << "1. Da" << std::endl;
											std::cout << "2. Ne, zelim da unesem ponovo" << std::endl;
											std::cout << std::endl << "Odaberi opciju: "; std::cin >> isCorrect;
										}
									} while (isCorrect != '2' && isCorrect != '1');
								}
								if (!w)
								{
									system("cls");
									std::ofstream file;
									file.open("RegistrovaniAdmini.txt", std::ios::app);
									file << std::setw(15) << std::left << a.getName() << std::setw(15) << std::left << a.getSurname() << std::setw(10) << std::left << a.getID() << std::setw(10) << std::left << a.getPIN() << std::setw(10) << std::left << a.getMalicious() << std::endl;
									std::cout << "Novi administrator je uspjesno registrovan, njegovi podaci su:" << std::endl;
									std::cout << std::endl;
									a.printPerson();
									getchar();
									getchar();
									file.close();
								}
							}
							if (user == '2')
							{
								char isCorrect = '2';
								Person a;
								int w;
								while (isCorrect == '2')
								{
									int IDlength = 0;
									do
									{
										system("cls");
										std::cout << "TURBO TOTAL 2000" << std::endl;
										std::cout << std::endl << "REGISTRACIJA NOVOG ANALITICARA" << std::endl;
										std::cout << std::endl;
										IDlength = a.readPerson();
									} while (IDlength == 0);
									w = isThereAnalyst(a);
									do
									{
										system("cls");
										std::cout << "Podaci koje ste unijeli: " << std::endl << std::endl;
										a.printPerson();
										if (w)
										{
											char y;
											do
											{
												system("cls");
												std::cout << "Podaci koje ste unijeli: " << std::endl << std::endl;
												a.printPerson();
												std::cout << std::endl << "Greska! Vec postoji analiticar sa takvim podacima." << std::endl;
												std::cout << std::endl << "Da li zelite ponovo pokusati registrovati novog analiticara?" << std::endl;
												std::cout << "1. Da" << std::endl;
												std::cout << "2. Ne" << std::endl;
												std::cout << std::endl << "Unesi opciju: "; std::cin >> y;
											} while (y != '1' && y != '2');
											if (y == '1')
											{
												isCorrect = '2';
											}
											if (y == '2')
											{
												isCorrect = '1';
											}
										}
										else
										{
											std::cout << std::endl << "Da li su ovo podaci koje ste htjeli unijeti?" << std::endl;
											std::cout << std::endl << "1. Da" << std::endl;
											std::cout << "2. Ne, zelim da unesem ponovo" << std::endl;
											std::cout << std::endl << "Odaberi opciju: "; std::cin >> isCorrect;
										}
									} while (isCorrect != '2' && isCorrect != '1');
								}
								if (!w)
								{
									system("cls");
									std::ofstream file;
									file.open("RegistrovaniAnaliticari.txt", std::ios::app);
									file << std::setw(15) << std::left << a.getName() << std::setw(15) << std::left << a.getSurname() << std::setw(10) << std::left << a.getID() << std::setw(10) << std::left << a.getPIN() << std::setw(10) << std::left << a.getMalicious() << std::endl;
									std::cout << "Novi analiticar je uspjesno registrovan, njegovi podaci su:" << std::endl;
									std::cout << std::endl;
									a.printPerson();
									getchar();
									getchar();
									file.close();
								}
							}
						}
						////////////////////////////////////////////ispis korisnika
						if (option1 == '2')
						{
							char user;
							do
							{
								system("cls");
								std::cout << "ISPIS KORISNIKA" << std::endl;
								std::cout << std::endl << "Odaberi korisnicku klasu: " << std::endl;
								std::cout << std::endl << "1. Administrator" << std::endl;
								std::cout << "2. Analiticar" << std::endl;
								std::cout << std::endl << "Odaberi opciju: "; std::cin >> user;
							} while (user != '1' && user != '2');
							if (user == '1')
							{
								std::string line;
								std::ifstream myfile("RegistrovaniAdmini.txt");
								if (myfile.is_open())
								{
									system("cls");
									int i = 0;
									std::cout << "SPISAK ADMINISTRATORA" << std::endl << std::endl;
									printPersonHeader();
									while (getline(myfile, line))
									{
										std::cout << ++i << ". " << line << std::endl;
									}
									printPersonFooter();
									getchar();
									getchar();
									myfile.close();
								}
								else
								{
									std::cout << "Datoteka nije uspjesno otvorena";
									getchar();
									getchar();
								}
							}
							if (user == '2')
							{
								std::string line;
								std::ifstream myfile("RegistrovaniAnaliticari.txt");
								if (myfile.is_open())
								{
									system("cls");
									int i = 0;
									std::cout << "SPISAK ANALITICARA" << std::endl << std::endl;
									printPersonHeader();
									while (getline(myfile, line))
									{
										std::cout << ++i << ". " << line << std::endl;
									}
									printPersonFooter();
									getchar();
									getchar();
									myfile.close();
								}
								else
								{
									std::cout << "Datoteka nije uspjesno otvorena";
									getchar();
									getchar();
								}
							}
						}
						//////////////////////////////////////////////brisanje korisnika
						if (option1 == '3')
						{
							char option3;
							do
							{
								system("cls");
								std::cout << "BRISANJE KORISNIKA" << std::endl;
								std::cout << std::endl << "1. Obrisi administratora" << std::endl;
								std::cout << "2. Obrisi analiticara" << std::endl;
								std::cout << std::endl << "Unesi opciju: "; std::cin >> option3;
							} while (option3 != '1' && option3 != '2');

							if (option3 == '1')
							{
								system("cls");
								std::string string;
								std::cout << "BRISANJE ADMINISTRATORA" << std::endl << std::endl;
								char name[15], surname[15], ID[15], PIN[15], maliciozan[15];
								FILE* d;
								d = fopen("RegistrovaniAdmini.txt", "r");
								std::vector<Person> vec;
								while (fscanf(d, "%s %s %s %s %s\n", name, surname, ID, PIN, maliciozan) == 5)
								{
									Person b;
									std::string nname(name); b.setName(nname);
									std::string ssurname(surname); b.setSurname(ssurname);
									std::string PPIN(PIN); b.setPIN(PPIN);
									std::string IID(ID); b.setID(IID);
									std::string mmaliciozan(maliciozan); b.setMalicious(mmaliciozan);
									vec.push_back(b);
								}
								fclose(d);

								printPersonHeader();
								for (int i = 0; i<vec.size(); i++)
									std::cout << i + 1 << ". " << std::setw(15) << std::left << vec[i].getName() << std::setw(15) << std::left << vec[i].getSurname() << std::setw(10) << std::left << vec[i].getID() << std::setw(10) << std::left << vec[i].getPIN() << std::setw(10) << std::left << vec[i].getMalicious() << std::endl;
								printPersonFooter();

								std::cout << std::endl << "Unesite ID administratora kojeg zelite obrisati: "; std::cin >> string;
								int isDeleted = deleteAdmin(string);
								if (isDeleted)
								{
									std::cout << std::endl << "Administrator je uspjesno obrisan."; getchar(); getchar();
								}
								else
								{
									std::cout << std::endl << "Ne postoji administrator sa unesenim ID-om."; getchar(); getchar();
								}
							}
							if (option3 == '2')
							{
								system("cls");
								std::string string;
								std::cout << "BRISANJE ANALITICARA" << std::endl << std::endl;

								char name[15], surname[15], ID[15], PIN[15], maliciozan[15];
								FILE* d;
								d = fopen("RegistrovaniAnaliticari.txt", "r");
								std::vector<Person> vec;
								while (fscanf(d, "%s %s %s %s %s\n", name, surname, ID, PIN, maliciozan) == 5)
								{
									Person b;
									std::string nname(name); b.setName(nname);
									std::string ssurname(surname); b.setSurname(ssurname);
									std::string PPIN(PIN); b.setPIN(PPIN);
									std::string IID(ID); b.setID(IID);
									std::string mmaliciozan(maliciozan); b.setMalicious(mmaliciozan);
									vec.push_back(b);
								}
								fclose(d);

								printPersonHeader();
								for (int i = 0; i<vec.size(); i++)
									std::cout << i + 1 << ". " << std::setw(15) << std::left << vec[i].getName() << std::setw(15) << std::left << vec[i].getSurname() << std::setw(10) << std::left << vec[i].getID() << std::setw(10) << std::left << vec[i].getPIN() << std::setw(10) << std::left << vec[i].getMalicious() << std::endl;
								printPersonFooter();

								std::cout << std::endl << "Unesite ID analiticara kojeg zelite obrisati: "; std::cin >> string;
								int isDeleted = deleteAnalyst(string);
								if (isDeleted)
								{
									std::cout << std::endl << "Analiticar je uspjesno obrisan!!!"; getchar(); getchar();
								}
								else
								{
									std::cout << std::endl << "Ne postoji analiticar sa unesenim ID-om"; getchar(); getchar();
								}
							}
						}
						/////////////////odobravanje pristupa sistemu
						if (option1 == '4')
						{
							char user;
							do
							{
								system("cls");
								std::cout << "ODOBRAVANJE PRISTUPA SISTEMU" << std::endl;
								std::cout << std::endl << "1. Odobravanje pristupa administratoru" << std::endl;
								std::cout << "2. Odobravanje pristupa analiticaru" << std::endl;
								std::cout << std::endl << "Unesi opciju: "; std::cin >> user;
							} while (user != '1' && user != '2');
							if (user == '1')
							{
								/////////////promjena statusa admina za odrenjeni ID
								system("cls");
								std::string id;
								char name[15], surname[15], ID[15], PIN[15], maliciozan[15];
								FILE* myfile;
								std::cout << "ODOBRAVANJE PRISTUPA ADMINISTRATORU" << std::endl;

								FILE* d;
								d = fopen("MaliciozniAdmini.txt", "r");
								std::vector<Person> vec;
								while (fscanf(d, "%s %s %s %s %s\n", name, surname, ID, PIN, maliciozan) == 5)
								{
									Person b;
									std::string nname(name); b.setName(nname);
									std::string ssurname(surname); b.setSurname(ssurname);
									std::string PPIN(PIN); b.setPIN(PPIN);
									std::string IID(ID); b.setID(IID);
									std::string mmaliciozan(maliciozan); b.setMalicious(mmaliciozan);
									vec.push_back(b);
								}
								fclose(d);
								if (vec.size())
								{
									std::cout << std::endl << "Spisak malicioznih admina: " << std::endl;
									printPersonHeader();
									for (int i = 0; i < vec.size(); i++)
										std::cout << i + 1 << ". " << std::setw(15) << std::left << vec[i].getName() << std::setw(15) << std::left << vec[i].getSurname() << std::setw(10) << std::left << vec[i].getID() << std::setw(10) << std::left << vec[i].getPIN() << std::setw(10) << std::left << vec[i].getMalicious() << std::endl;
									printPersonFooter();

									std::cout << std::endl << "Unesite ID administratora kojem zelite odobriti pristup: "; std::cin >> id;
									if (isThereMaliciousAdmin(id))
									{
										std::cout << std::endl << "Administratoru sa unesenim ID-om je omoguceno pravo pristupa sistemu." << std::endl;
										FILE* file;
										file = fopen("RegistrovaniAdmini.txt", "r");
										std::vector<Person> v;
										while (fscanf(file, "%s %s %s %s %s\n", name, surname, ID, PIN, maliciozan) == 5)
										{
											Person b;
											std::string nname(name); b.setName(nname);
											std::string ssurname(surname); b.setSurname(ssurname);
											std::string PPIN(PIN); b.setPIN(PPIN);
											std::string IID(ID); b.setID(IID);
											std::string mmaliciozan(maliciozan); b.setMalicious(mmaliciozan);
											v.push_back(b);
										}

										for (int i = 0; i < v.size(); i++)
											if (v[i].getID() == id)
											{
												v[i].getMalicious() = "odobren";
											}

										fclose(file);
										std::ofstream f;
										f.open("RegistrovaniAdmini.txt");
										for (int i = 0; i < v.size(); i++)
											f << std::setw(15) << std::left << v[i].getName() << std::setw(15) << std::left << v[i].getSurname() << std::setw(10) << std::left << v[i].getID() << std::setw(10) << std::left << v[i].getPIN() << std::setw(10) << std::left << v[i].getMalicious() << std::endl;
										f.close();



										/////////////////brisanje malicioznih admina iz MaliciozniAdmini.txt
										for (int i = 0; i < vec.size(); i++)
											if (vec[i].getID() == id)
											{
												vec.erase(vec.begin() + i);
											}
										std::ofstream filee;
										filee.open("MaliciozniAdmini.txt");
										for (int i = 0; i < vec.size(); i++)
											filee << std::setw(15) << std::left << vec[i].getName() << std::setw(15) << std::left << vec[i].getSurname() << std::setw(10) << std::left << vec[i].getID() << std::setw(10) << std::left << vec[i].getPIN() << std::setw(10) << std::left << vec[i].getMalicious() << std::endl;
										filee.close();
									}
									else
									{
										std::wcout << std::endl << "Ne postoji maliciozan administrator sa unesenim ID-om!" << std::endl;
									}
								}
								else
								{
									std::cout << std::endl << "Nijedan od administratora nije maliciozan." << std::endl;
								}
							}
							if (user == '2')
							{
								/////////////promjena statusa analiticara za odrenjeni ID
								system("cls");
								std::string id;
								char name[15], surname[15], ID[15], PIN[15], maliciozan[15];
								FILE* myfile;
								std::cout << "ODOBRAVANJE PRISTUPA ANALITICARU" << std::endl;

								FILE* d;
								d = fopen("MaliciozniAnaliticari.txt", "r");
								std::vector<Person> vec;
								while (fscanf(d, "%s %s %s %s %s\n", name, surname, ID, PIN, maliciozan) == 5)
								{
									Person b;
									std::string nname(name); b.setName(nname);
									std::string ssurname(surname); b.setSurname(ssurname);
									std::string PPIN(PIN); b.setPIN(PPIN);
									std::string IID(ID); b.setID(IID);
									std::string mmaliciozan(maliciozan); b.setMalicious(mmaliciozan);
									vec.push_back(b);
								}
								fclose(d);
								if (vec.size())
								{
									std::cout << std::endl << "Spisak malicioznih analiticara: " << std::endl;
									printPersonHeader();
									for (int i = 0; i < vec.size(); i++)
										std::cout << i + 1 << ". " << std::setw(15) << std::left << vec[i].getName() << std::setw(15) << std::left << vec[i].getSurname() << std::setw(10) << std::left << vec[i].getID() << std::setw(10) << std::left << vec[i].getPIN() << std::setw(10) << std::left << vec[i].getMalicious() << std::endl;
									printPersonFooter();

									std::cout << std::endl << "Unesite ID analiticara kojem zelite odobriti pristup: "; std::cin >> id;

									if (isThereMaliciousAnalyst(id))
									{
										std::cout << std::endl << "Analiticaru sa unesenim ID-om je omoguceno pravo pristupa sistemu." << std::endl;
										FILE* file;
										file = fopen("RegistrovaniAnaliticari.txt", "r");
										std::vector<Person> v;
										while (fscanf(file, "%s %s %s %s %s\n", name, surname, ID, PIN, maliciozan) == 5)
										{
											Person b;
											std::string nname(name); b.setName(nname);
											std::string ssurname(surname); b.setSurname(ssurname);
											std::string PPIN(PIN); b.setPIN(PPIN);
											std::string IID(ID); b.setID(IID);
											std::string mmaliciozan(maliciozan); b.setMalicious(mmaliciozan);
											v.push_back(b);
										}

										for (int i = 0; i < v.size(); i++)
											if (v[i].getID() == id)
											{
												v[i].getMalicious() = "odobren";
											}

										fclose(file);
										std::ofstream f;
										f.open("RegistrovaniAnaliticari.txt");
										for (int i = 0; i < v.size(); i++)
											f << std::setw(15) << std::left << v[i].getName() << std::setw(15) << std::left << v[i].getSurname() << std::setw(10) << std::left << v[i].getID() << std::setw(10) << std::left << v[i].getPIN() << std::setw(10) << std::left << v[i].getMalicious() << std::endl;
										f.close();

										/////////////////brisanje malicioznih analiticara iz MaliciozniAnaliticari.txt
										for (int i = 0; i < vec.size(); i++)
											if (vec[i].getID() == id)
											{
												vec.erase(vec.begin() + i);
											}

										std::ofstream filee;
										filee.open("MaliciozniAnaliticari.txt");
										for (int i = 0; i < vec.size(); i++)
											filee << std::setw(15) << std::left << vec[i].getName() << std::setw(15) << std::left << vec[i].getSurname() << std::setw(10) << std::left << vec[i].getID() << std::setw(10) << std::left << vec[i].getPIN() << std::setw(10) << std::left << vec[i].getMalicious() << std::endl;
										filee.close();
									}
									else
									{
										std::wcout << std::endl << "Ne postoji maliciozan analiticar sa unesenim ID-om!" << std::endl;
									}
								}

								else
								{
									std::cout << std::endl << "Nijedan od analiticara nije maliciozan." << std::endl;
								}
							}
						}

					}
					do
					{
						std::cout << std::endl << "0. Odjavi se" << std::endl;
						std::cout << "1. Vrati se na pocetak profila" << std::endl;
						std::cout << "2. Izadji iz aplikacije" << std::endl;
						std::cout << std::endl << "Unesi opciju: "; std::cin >> t;
						if (t == '0') kraj = 1;
						if (t == '2')
						{
							kraj = 0;
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

	if (!i && (p == 2 || p == 3))
	{
		if (p == 2)
		{
			std::string pom = a.getID();
			char name[15], surname[15], ID[15], PIN[15], maliciozan[15];
			FILE* myfile;
			myfile = fopen("RegistrovaniAdmini.txt", "r");
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
					v[i].getMalicious() = "onemogucen";
					if (maliciousAdmin(v[i]))
					{
						std::ofstream f;
						f.open("MaliciozniAdmini.txt", std::ios::app);
						f << std::setw(15) << std::left << v[i].getName() << std::setw(15) << std::left << v[i].getSurname() << std::setw(10) << std::left << v[i].getID() << std::setw(10) << std::left << v[i].getPIN() << std::setw(10) << std::left << v[i].getMalicious() << std::endl;
						f.close();
					}
				}
			}
			std::ofstream file;
			file.open("RegistrovaniAdmini.txt");
			for (int i = 0; i < v.size(); i++)
				file << std::setw(15) << std::left << v[i].getName() << std::setw(15) << std::left << v[i].getSurname() << std::setw(10) << std::left << v[i].getID() << std::setw(10) << std::left << v[i].getPIN() << std::setw(10) << std::left << v[i].getMalicious() << std::endl;
			file.close();
		}
		if (p == 3)
		{
			std::string pom = a.getPIN();
			char name[15], surname[15], ID[15], PIN[15], maliciozan[15];
			FILE* myfile;
			myfile = fopen("RegistrovaniAdmini.txt", "r");
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
				if (v[i].getPIN() == pom)
				{
					v[i].getMalicious() = "onemogucen";
					if (maliciousAdmin(v[i]))
					{
						std::ofstream f;
						f.open("MaliciozniAdmini.txt", std::ios::app);
						f << std::setw(15) << std::left << v[i].getName() << std::setw(15) << std::left << v[i].getSurname() << std::setw(10) << std::left << v[i].getID() << std::setw(10) << std::left << v[i].getPIN() << std::setw(10) << std::left << v[i].getMalicious() << std::endl;
						f.close();
					}
				}
			}
			std::ofstream file;
			file.open("RegistrovaniAdmini.txt");
			for (int i = 0; i < v.size(); i++)
				file << std::setw(15) << std::left << v[i].getName() << std::setw(15) << std::left << v[i].getSurname() << std::setw(10) << std::left << v[i].getID() << std::setw(10) << std::left << v[i].getPIN() << std::setw(10) << std::left << v[i].getMalicious() << std::endl;
			file.close();
		}
		system("cls");
		std::cout << "Pogresno ste unijeli podatke za prijavu 3x." << std::endl;
		std::cout << std::endl << "Da biste opet imali pristup sistemu, kontaktirajte administratora." << std::endl;
	}
	getchar();
}