#pragma once
#include "Person.h"
#include <vector>
#include <fstream>
#include <iomanip>
#include "Report.h"
#include "BillsReader.h"

void printPersonHeader();
void printPersonFooter();
int checkForAdmin(std::string,std::string);
int checkForAnalyst(std::string,std::string);
int deleteAnalyst(std::string);
int deleteAdmin(std::string);
int maliciousAdmin(Person);
int maliciousAnalyst(Person);
int isThereAdmin(Person);
int isThereMaliciousAdmin(std::string);
int isThereAnalyst(Person);
int isThereMaliciousAnalyst(std::string);
void AdminAnalystChoose(char&);
bool is_file_exist(const char*);
bool Admin_ID(std::string);
bool Admin_PIN(std::string);
bool Analyst_ID(std::string);
bool Analyst_PIN(std::string);
