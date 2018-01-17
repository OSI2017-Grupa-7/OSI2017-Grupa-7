#pragma once
#include "Article.h"
#include "Date.h"
#include <fstream>
#include <vector>
#include <string>
class ArticleReport {

	Date date;
	Article article;
	std::string buyer_name;

public:
	ArticleReport();
	~ArticleReport();
	void setDate(Date);
	void print();
	Date getDate()const;
	void setBuyerName(std::string);
	std::string getBuyerName() const;
	void setArticle(Article);
	Article getArticle();
};
void processingArticleReports(std::string);
void printArticleReports(std::vector<ArticleReport>);
void printHeaderArticle();//zaglavlje izvjestaja
void printFooterArticle();
Date parsingDate(std::string);
void sortReports(std::vector<ArticleReport>&);


