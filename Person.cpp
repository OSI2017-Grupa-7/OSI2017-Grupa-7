#include "Person.h"

int Person::readPerson()
{
	std::cout << "Ime: "; std::cin >> name;
	std::cout << "Prezime: "; std::cin >> surname;
	std::cout << "ID: "; std::cin >> ID;
	std::cout << "PIN: "; std::cin >> PIN;
	if (ID.length() != 4)
	{
		std::cout << std::endl << "ID mora imati 4 broja, pokusajte ponovo." << std::endl;
		getchar(); getchar();
		return 0;
	}
	return 1;
}

void Person::readPersonForLogin()
{
	std::cout << "ID: "; std::cin >> ID;
	std::cout << "PIN: "; std::cin >> PIN;
}

void Person::printPerson()
{
	std::cout << "Ime: " <<name<< std::endl;
	std::cout << "Prezime: " << surname << std::endl;
	std::cout << "ID: " << ID << std::endl;
	std::cout << "PIN: " << PIN << std::endl;
}

std::string Person::getName() { return name;}

std::string Person::getSurname() { return surname;}

std::string Person::getPIN() { return PIN;}

std::string Person::getID() { return ID;}

std::string& Person::getMalicious() { return maliciozan; }

void Person::setName(std::string a) { name = a;}

void Person::setSurname(std::string a) { surname = a;}

void Person::setID(std::string a) { ID = a;}

void Person::setPIN(std::string a) { PIN = a;}

void Person::setMalicious(std::string a) { maliciozan = a;}

bool Person::operator==(Person& a)
{
	if (name == a.name && surname == a.surname && ID == a.ID&& PIN == a.PIN)
		return true;
	else return false;
}

Person::Person() {}

Person::~Person() {}