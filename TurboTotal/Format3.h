#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BillsReader.h"

std::ifstream& GotoLine(std::ifstream&, unsigned int);// prelazi na odgovarajucu liniju u datoteci 
void parse(std::string&, std::string&, double&, int&);// izdvajanje informacija iz ucitanog racuna
void format3(std::string&);//ucitavanje racuna i ispis informacija u odgovarajuce datoteke
void parseDate(const std::string&, int&, int&, int&);//izdvajanje dana, mjeseca i godine kao posebne varijable
