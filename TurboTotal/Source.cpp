#include "Report.h"
#include "Pretprogram.h"
#include "AdminFunctionals.h"
#include "AnalystFunctionals.h"
#include "Logo.h"
#include <windows.h>
#include <cstdlib>
int application_exit = 1;//promjenjiva koja regulise konstantan rad aplikacije dok god korisnik ne pozeli izaci iz iste

int main()
{
	/////
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	startLogo();
	timer(3);
	system("cls");
	////omogucava otvaranje full screen konzole, ispisuje logo, ispis traje 3sekunde
	Pretprogram();
	while (application_exit)
	{
		char option;
		AdminAnalystChoose(option);
		if (option == '1') { AdminFunctionals(); }
		if (option == '2') { AnalystFunctionals(); }
	}
}