#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <experimental/filesystem>


std::vector<std::string> get_filenames(std::experimental::filesystem::path);
void billsReading();
int billFormat();