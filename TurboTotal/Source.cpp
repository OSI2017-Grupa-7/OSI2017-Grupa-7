#include "Report.h"
#include "Pretprogram.h"
#include "AdminFunctionals.h"
#include "AnalystFunctionals.h"
#include "Logo.h"
#include <windows.h>
#include <cstdlib>
int kraj = 1;

int main()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	startLogo();
	int i = 0;
	while (i < 1000000000)
	{
		i++;
	} 
	system("cls");
	Pretprogram();
	while (kraj)
	{
		char option;
		AdminAnalystChoose(option);
		if (option == '1') { AdminFunctionals(); }
		if (option == '2') { AnalystFunctionals(); }
	}
}