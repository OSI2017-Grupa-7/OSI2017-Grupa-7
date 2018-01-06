#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

void format5Processing(std::string);
void findNameSurnameDate(std::string, std::string&, std::string&);//fja koja iz imena pokupi ime prezime i datum
void findArticles(std::string, std::string);
void removeBillProcessed(std::vector<std::string>);
void putArticles(std::string, std::string, std::string);
int validation(std::string);