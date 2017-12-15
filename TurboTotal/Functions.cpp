#include "Functions.h"

extern int kraj;

void AdminAnalystChoose(char &option)
{
	do {
		system("cls");
		std::cout << "TURBO TOTAL 2000" << std::endl;
		std::cout << std::endl << "Pristupam sistemu kao:" << std::endl;
		std::cout <<std::endl<< "1. Administrator" << std::endl;
		std::cout << "2. Analiticar" << std::endl;
		std::cout << std::endl << "Odaberi opciju: "; std::cin >> option;
	} while (option != '1' && option != '2');
}


void printPersonHeader()
{
	std::cout << "====================================================================" << std::endl;
	std::cout << "RB.IME            PREZIME        ID       PIN        PRISTUP        " << std::endl;
	std::cout << "====================================================================" << std::endl;
}

void printPersonFooter() { std::cout << std::endl << "====================================================================" << std::endl; }


int checkForAdmin(std::string a, std::string b)
{
	char name[15], surname[15], ID[15], PIN[15], maliciozan[15];
	FILE* myfile;
	myfile = fopen("RegistrovaniAdmini.txt", "r");
	while (fscanf(myfile, "%s %s %s %s %s\n", name, surname, ID, PIN, maliciozan) == 5)
	{
		std::string IID(ID);
		std::string PPIN(PIN);
		std::string mmaliciozan(maliciozan);
		if (IID == a && PPIN == b)
		{
			if (mmaliciozan == "onemogucen")
			{
				return 5;
			}
		}
	}

	myfile = fopen("RegistrovaniAdmini.txt", "r");
	while (fscanf(myfile, "%s %s %s %s %s\n", name, surname, ID, PIN, maliciozan) == 5)
	{
		std::string IID(ID);
		std::string PPIN(PIN);
		if (IID == a && PPIN == b)
			return 1;
		else if (IID == a && PPIN != b)
			return 2;
		else if (IID != a && PPIN == b)
			return 3;
	}
	return 0;
}

int checkForAnalyst(std::string a, std::string b)
{
	char name[15], surname[15], ID[15], PIN[15], maliciozan[15];
	FILE* myfile;
	myfile = fopen("RegistrovaniAnaliticari.txt", "r");
	while (fscanf(myfile, "%s %s %s %s %s\n", name, surname, ID, PIN, maliciozan) == 5)
	{
		std::string IID(ID);
		std::string PPIN(PIN);
		std::string mmaliciozan(maliciozan);
		if (IID == a && PPIN == b)
		{
			if (mmaliciozan == "onemogucen")
			{
				return 5;
			}
		}
	}

	myfile = fopen("RegistrovaniAnaliticari.txt", "r");
	while (fscanf(myfile, "%s %s %s %s %s\n", name, surname, ID, PIN,maliciozan) == 5)
	{
		std::string IID(ID);
		std::string PPIN(PIN);
		if (IID == a && PPIN == b)
			return 1;
		else if (IID == a && PPIN !=b)
			return 2;
		else if (IID != a && PPIN == b)
			return 3;
	}
	return 0;
}

int deleteAnalyst(std::string a)
{
	short isString=0;
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

	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i].getID() == a)
			isString = 1;
	if (isString == 0)
		return 0;
	std::ofstream file;
	file.open("RegistrovaniAnaliticari.txt");
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i].getID() == a)
			v.erase(v.begin() + i);

	for (unsigned int i = 0; i < v.size(); i++)
	   file << std::setw(15) << std::left << v[i].getName() << std::setw(15) << std::left << v[i].getSurname() << std::setw(10) << std::left << v[i].getID() << std::setw(10) << std::left << v[i].getPIN() << std::setw(10) << std::left << v[i].getMalicious() << std::endl;
	file.close();
	return 1;
}

int deleteAdmin(std::string a)
{
	short isString = 0;
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

	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i].getID() == a)
			isString = 1;
	if (isString == 0)
		return 0;
	std::ofstream file;
	file.open("RegistrovaniAdmini.txt");
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i].getID() == a)
			v.erase(v.begin() + i);

	for (unsigned int i = 0; i < v.size(); i++)
		file << std::setw(15) << std::left << v[i].getName() << std::setw(15) << std::left << v[i].getSurname() << std::setw(10) << std::left << v[i].getID() << std::setw(10) << std::left << v[i].getPIN() << std::setw(10) << std::left << v[i].getMalicious() << std::endl;
	file.close();
	return 1;
}

int maliciousAdmin(Person a)
{
	char name[15], surname[15], ID[15], PIN[15], maliciozan[15];
	FILE* myfile;
	myfile = fopen("MaliciozniAdmini.txt", "r");
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
	
	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (a.getID() == v[i].getID())
			return 0 ;
	}
	return 1;

}

int maliciousAnalyst(Person a)
{
	char name[15], surname[15], ID[15], PIN[15], maliciozan[15];
	FILE* myfile;
	myfile = fopen("MaliciozniAnaliticari.txt", "r");
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

	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (a.getID() == v[i].getID())
			return 0;
	}
	return 1;
}

int isThereAdmin(Person a)
{
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
	
	for (unsigned int i = 0; i < v.size(); i++)
	{
		if ((a.getName() == v[i].getName() && a.getSurname() == v[i].getSurname() && a.getPIN() == v[i].getPIN() && a.getID() == v[i].getID()) 
			|| (a.getID()==v[i].getID())
			|| (a.getPIN()==v[i].getPIN()))
			return 1;
	}
	return 0;
}

int isThereMaliciousAdmin(std::string a)
{
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

	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (v[i].getID()==a)
			return 1;
	}
	return 0;
}

int isThereAnalyst(Person a)
{
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

	for (unsigned int i = 0; i < v.size(); i++)
	{
		if((a.getName() == v[i].getName() && a.getSurname() == v[i].getSurname() && a.getPIN() == v[i].getPIN() && a.getID() == v[i].getID())
			|| (a.getID() == v[i].getID())
			|| (a.getPIN() == v[i].getPIN()))
			return 1;
	}
	return 0;
}

int isThereMaliciousAnalyst(std::string a)
{
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

	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (v[i].getID() == a)
			return 1;
	}
	return 0;
}

