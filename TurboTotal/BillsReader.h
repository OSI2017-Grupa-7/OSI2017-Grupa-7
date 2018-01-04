#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <experimental/filesystem>


std::vector<std::string> get_filenames(std::experimental::filesystem::path);
void billsReading();
int billFormat(std::vector<std::string>);
void format5Processing(std::string);
void findNameSurnameDate(std::string, std::string&, std::string&);//fja koja iz imena pokupi ime prezime i datum
void findArticles(std::string, std::string);
void removeBillProcessed(std::vector<std::string>);