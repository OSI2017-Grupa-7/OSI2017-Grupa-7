#include "ArticleReport.h"
#include <sstream>


double total_total = 0, total_amount = 0;//ukupna cijena i kolicina svih kupovina datog artikla

ArticleReport::ArticleReport()
{
}

ArticleReport::~ArticleReport()
{
}
void ArticleReport::setDate(Date d)
{
	date = d;
}
void ArticleReport::print()
{
	std::ifstream file("Valuta.txt");
	std::string value;
	file >> value;
	file.close();
	double pr = article.getPrice();
	double tot = article.getTotal();
	std::ostringstream os;
	os << pr;
	std::string pr_value = os.str() + ' ' + value;

	std::ostringstream oss;
	oss << tot;
	std::string tot_value = oss.str() + ' ' + value;


	std::cout <<std::endl<<std::endl << "Datum: "; date.print();
	std::cout << "Kupac: " << buyer_name;
	printHeaderArticle();
	std::cout << " " << std::left << std::setw(10) <<article.getAmount() << std::left << std::setw(8) << pr_value << std::left << std::setw(10) << tot_value;
	printFooterArticle();
}
Date ArticleReport::getDate() const
{
	return date;
}
void ArticleReport::setBuyerName(std::string b_name)
{
	buyer_name = b_name;
}
std::string ArticleReport::getBuyerName() const
{
	return buyer_name;
}
void ArticleReport::setArticle(Article art)
{
	article = art;
}
Article ArticleReport::getArticle()
{
	return article;
}
void printHeaderArticle()
{
	std::cout << std::endl << "=================================" << std::endl;
	std::cout << " KOLICINA  CIJENA  UKUPNO" << std::endl;
	std::cout << "=================================" << std::endl;
}

void printFooterArticle()
{
	std::cout <<std::endl<< "=================================" << std::endl;
}
void processingArticleReports(std::string file_name) {
	std::vector<ArticleReport> vec;
	std::string line;
	int counter = 0;
	std::ifstream file("Artikli/" + file_name + ".txt");
	if (!file.is_open()) std::cout << std::endl << "Ne postoji artikal sa tom sifrom.";
	else {
		while (getline(file, line)) {
			if(line[0]== '-')
			counter++;
		}
		file.clear();
		file.seekg(file.beg);
		while (counter--) {
			ArticleReport artRep;
			Article art;
			std::string am, pr, tot,pom;
			getline(file, line);
			artRep.setBuyerName(line);
			getline(file, line);
			artRep.setDate(parsingDate(line));
			file >> am >> pr >> tot;
			total_total += stod(tot);
			total_amount += stod(am);
			art.setAmount(stod(am));
			art.setPrice(stod(pr));
			art.setTotal(stod(tot));
			artRep.setArticle(art);
			vec.push_back(artRep);
			getline(file, pom); //hvata footer
			getline(file, pom);
		}
	}
	printArticleReports(vec);
}
Date parsingDate(std::string date) {
	Date d;
	int i;
	std::string day, month, year;
	for (i = 0; i < date.length(); i++)
		if (date[i] != '.')
			day += date[i];
		else break;
		d.setDay(stoi(day));
		i++;
		for (i; i < date.length(); i++)
			if (date[i] != '.')
				month += date[i];
			else break;
			d.setMonth(stoi(month));
			i++;
			for (i; i < date.length(); i++)
				if (date[i] != '.')
					year += date[i];
				else break;
				d.setYear(stoi(year));

				return d;
}
void printArticleReports(std::vector<ArticleReport> vect) {
	sortReports(vect);
	std::ifstream file("Valuta.txt");
	std::string value;
	file >> value;
	file.close();

	std::ostringstream os;
	os << total_total;
	std::string total_total_value = os.str() + ' ' + value;
	std::ostringstream oss;
	double pdv = total_total*0.17;
	oss << pdv;
	std::string pdv_value = oss.str() + ' ' + value;
	std::ostringstream osss;
	double with_PDV = total_total + pdv;
	osss << with_PDV;
	std::string with_PDV_value = osss.str() + ' ' + value;
	for (unsigned int i = 0; i < vect.size(); i++)
		vect[i].print();

	std::cout << "KONACNO: " << std::endl;
	std::cout << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << "  " << "KOLICINA" << "     " << "UKUPNO BEZ PDV" << "     " << "PDV" << "           " << "UKUPNO" << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << "  " << std::left << std::setw(13) << total_amount << std::left << std::setw(19) << total_total_value << std::left << std::setw(14) << pdv_value << std::left << std::setw(2) << with_PDV_value << std::endl;
	std::cout << "========================================================" << std::endl;
	getchar();
}

void sortReports(std::vector<ArticleReport>& vect) {
	unsigned int i, j;
	for (i = 0; i < vect.size() - 1; i++)
		for (j = 0; j < vect.size() - i - 1; j++)
			if ((vect[j].getDate() < vect[j + 1].getDate()))
			{
				ArticleReport a = vect[j];
				vect[j] = vect[j + 1];
				vect[j + 1] = a;
			}
}