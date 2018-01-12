#pragma once
#include <vector>
#include "Article.h"




void format2Processing(std::string);//funkcija koja vrsi obradu Formata2
void buyer_file_output(std::string, std::string, std::vector<Article>&, double, double, double);//funkcija koja upisuje podatke o kupcima u datoteku Kupac.txt
void article_file_output(std::string, std::string, std::string, Article&);//funkcija koja upisuje podatke o artiklima u datoteku Artikal.txt
void trim(std::string&);//pomocna funkcija koja brise space prije stringa i poslije stringa
