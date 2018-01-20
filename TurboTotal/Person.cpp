#include "Person.h"
#include <conio.h>

int Person::readPerson()
{
	std::cout << "Ime: "; std::cin >> name;
	std::cout << "Prezime: "; std::cin >> surname;
	std::cout << "ID: "; std::cin >> ID;
	std::cout << "PIN: "; std::cin >> PIN;
	if (ID.length() != 4 || PIN.length() != 4)
	{
		std::cout << std::endl << "ID i PIN moraju imati 4 broja, pokusajte ponovo." << std::endl;
		getchar(); getchar();
		return 0;
	}
	return 1;
}

void Person::readPersonForLogin()
{
	std::cout << "ID: "; std::cin >> ID;
	std::cout << "PIN: "; Mask(PIN);
}

void Person::printPerson()
{
	std::cout << "Ime: " << name << std::endl;
	std::cout << "Prezime: " << surname << std::endl;
	std::cout << "ID: " << ID << std::endl;
	std::cout << "PIN: " << PIN << std::endl;
}

std::string Person::getName() { return name; }

std::string Person::getSurname() { return surname; }

std::string Person::getPIN() { return PIN; }

std::string Person::getID() { return ID; }

std::string& Person::getMalicious() { return maliciozan; }

void Person::setName(std::string a) { name = a; }

void Person::setSurname(std::string a) { surname = a; }

void Person::setID(std::string a) { ID = a; }

void Person::setPIN(std::string a) { PIN = a; }

void Person::setMalicious(std::string a) { maliciozan = a; }

bool Person::operator==(Person& a)
{
	if (name == a.name && surname == a.surname && ID == a.ID&& PIN == a.PIN)
		return true;
	else return false;
}

Person::Person() {}

Person::~Person() {}

void Person::Mask(std::string& str) {
	int i = 0;
	char a;
	char arr[30];
	char *temp;
	while (1) {
		a = _getch();
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9')) {
			arr[i++] = a;
			std::cout << "*";
		}
		if (a == '\b' && i > 0) {
			std::cout << "\b \b";
			i--;
		}
		if (a == '\r') {
			arr[i] = '\0';
			break;
		}
	}
	temp = new char[i + i];
	for (int n = 0; n < i + 1; n++) {
		temp[n] = arr[n];
	}
	str = temp;
}