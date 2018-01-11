#include "BuyerReport.h"

void readForBuyerReport(std::string file_name) 
{
	std::string name_file = file_name + ".txt";
	std::ifstream file(name_file);
	std::string line("0");
	int d = 1, m = 1, g = 1,day,month,year;
	int date_control = 0,article_counter = 0,new_bill_counter=0;
	std::string pom;
	std::vector<Article> v;
	std::vector<BuyerReport> vec;

	if (file.is_open())
	{
		while (!file.eof())
		{
			v.erase(v.begin(),v.end());
			BuyerReport buyer_report;
			std::string end_of_bill;
			do
			{
				Article article;
				std::string date,code,name,amount,price,total;
				getline(file,date);//pronadjen datum jednog buyer_reporta
				end_of_bill = date;
				std::string articles,last_article;
				do
				{
					code.erase(); name.erase(); amount.erase(); price.erase(); total.erase();
					getline(file, articles);
					
					if (articles.length() < 10) { last_article = articles; break; };
					int i = 0;
					for (i; i < articles.length(); i++)
						if (articles[i] != ' ')
							code += articles[i];
						else break;
					i++;
					for (i; i < articles.length(); i++)
						if (articles[i] != ' ')
							name += articles[i];
						else break;
					i++;
					for (i; i < articles.length(); i++)
						if (articles[i] != ' ')
							amount += articles[i];
						else break;
					i++;
					for (i; i < articles.length(); i++)
						if (articles[i] != ' ')
							price += articles[i];
						else break;
					i++;
					for (i; i < articles.length(); i++)
						if (articles[i] != ' ')
							total += articles[i];
						else break;
			
			article.setCode(code);
			article.setName(name);
			article.setAmount(stod(amount));
			article.setPrice(stod(price));
			article.setTotal(stod(total));
			v.push_back(article);//dodan jedan artikal u vektor artikala
					
				} while (articles.length() > 10);

				std::string pdvs;
				
				////////////////////////////////
				std::string no_pdv=last_article;
				std::string pdv;
				std::string plus_pdv;
				file >> pdv;
				file >> plus_pdv;

				buyer_report.setNo_pdv(stod(no_pdv));
				buyer_report.setPdv(stod(pdv));
				buyer_report.setPlus_pdv(stod(plus_pdv));//pronadjene, setovane velicine bez pdv, pdv, sa pdv

				buyer_report.setDate(date);//setovan datum jednom buyer_reportu
				buyer_report.setVec(v);//setovan vektor artikala u jednom buyer_reportu
				vec.push_back(buyer_report);//dodan jedan buyer_report u vektor

				getline(file, end_of_bill);
				getline(file, end_of_bill);
			} while (end_of_bill[0] != '-');
	    }
	}
	
	else
	{
		std::cout << std::endl << "Ne postoji kupac sa tim imenom!!" << std::endl;
	}

	printBuyerReport(vec);
	getchar();
	getchar();
}

void printBuyerReport(std::vector<BuyerReport> vec)
{
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		std::cout << "===============" << std::endl;
		vec[i].print();
		std::cout << "================" << std::endl<<std::endl;
	}
}

BuyerReport::BuyerReport() {}

void BuyerReport::setDate(std::string d) { date = d;}

BuyerReport::~BuyerReport() {}

void BuyerReport::setNo_pdv(double d) { no_pdv = d;}

void BuyerReport::setPdv(double d) { pdv = d;}

void BuyerReport::setPlus_pdv(double d) { plus_pdv = d;}

void BuyerReport::setVec(std::vector<Article> v) { vec = v;}

void BuyerReport::print()
{
	std::cout <<"Datum: "<< date << std::endl<<std::endl;

	for (unsigned int i = 0; i < vec.size(); i++)
		 vec[i].print();
	
	std::cout << std::endl << "Bez PDV: " << no_pdv << std::endl;
	std::cout << "PDV: " << pdv << std::endl;
	std::cout << "Sa PDV: " << plus_pdv << std::endl;
	
}
