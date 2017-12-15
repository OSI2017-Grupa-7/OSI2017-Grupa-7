#include "AdminFunctionals.h"
#include "Functions.h"
extern int kraj;
void AdminFunctionals()
{
	Person a;
	int i = 3, k = 1, p;
	while (i && k)
	{
		system("cls");
		std::cout << "TURBO TOTAL 2000" << std::endl << std::endl << "PRIJAVA ZA ADMINISTRATORA" << std::endl << std::endl;
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
				int t = 1;
				while (t)
				{
					k = 0;
					short option1;
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
						} while (option1 != 1 && option1 != 2 && option1 != 3 && option1 != 4);
						/////////////////////////////////////////////////registracija korisnika
						if (option1 == 1)
						{
							short user;
							do
							{
								system("cls");
								std::cout << "REGISTRACIJA KORISNIKA" << std::endl;
								std::cout << std::endl << "Odaberi korisnicku klasu: " << std::endl;
								std::cout << std::endl << "1. Administrator" << std::endl;
								std::cout << "2. Analiticar" << std::endl;
								std::cout << std::endl << "Odaberi opciju: "; std::cin >> user;
							} while (user != 1 && user != 2);
							system("cls");
							if (user == 1)
							{
								short isCorrect = 2;
								Person a;
								int w;
								while (isCorrect == 2)
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
											int y;
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
											} while (y != 1 && y != 2);
											if (y == 1)
											{
												isCorrect = 2;
											}
											if (y == 2)
											{
												isCorrect = 1;
											}
										}
										else
										{
											std::cout << std::endl << "Da li su ovo podaci koje ste htjeli unijeti?" << std::endl;
											std::cout << std::endl << "1. Da" << std::endl;
											std::cout << "2. Ne, zelim da unesem ponovo" << std::endl;
											std::cout << std::endl << "Odaberi opciju: "; std::cin >> isCorrect;
										}
									} while (isCorrect != 2 && isCorrect != 1);
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
							if (user == 2)
							{
								short isCorrect = 2;
								Person a;
								int w;
								while (isCorrect == 2)
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
											int y;
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
											} while (y != 1 && y != 2);
											if (y == 1)
											{
												isCorrect = 2;
											}
											if (y == 2)
											{
												isCorrect = 1;
											}
										}
										else
										{
											std::cout << std::endl << "Da li su ovo podaci koje ste htjeli unijeti?" << std::endl;
											std::cout << std::endl << "1. Da" << std::endl;
											std::cout << "2. Ne, zelim da unesem ponovo" << std::endl;
											std::cout << std::endl << "Odaberi opciju: "; std::cin >> isCorrect;
										}
									} while (isCorrect != 2 && isCorrect != 1);
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
					}
				}
			}
		}
	}
}