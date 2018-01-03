#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "BillsReader.h"

std::ifstream& GotoLine(std::ifstream&, unsigned int);
void boi(std::string&, std::string&, double&, int&);
void format3(std::string&);
void parseDate(const std::string&, int&, int&, int&);
