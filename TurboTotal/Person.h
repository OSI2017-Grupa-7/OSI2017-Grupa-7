#pragma once
#include <iostream>
#include <string>
class Person
{
	std::string name, surname, ID, PIN, maliciozan = "odobren";
public:
	int readPerson();
	void readPersonForLogin();
	void printPerson();
	std::string getName();
	std::string getSurname();
	std::string getPIN();
	std::string getID();
	std::string& getMalicious();
	void setName(std::string);
	void setSurname(std::string);
	void setID(std::string);
	void setPIN(std::string);
	void setMalicious(std::string);
	bool operator==(Person&);
	Person();
	~Person();
	void Mask(std::string&);
};