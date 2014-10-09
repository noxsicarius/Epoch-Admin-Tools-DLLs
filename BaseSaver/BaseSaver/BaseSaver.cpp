// adminToolLog.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"

extern "C"
{
	__declspec(dllexport) void __stdcall RVExtension(char *output, int outputSize, char *function);
}

void __stdcall RVExtension(char *output, int outputSize, char *function)
{
	// Create folder if non-existant
	CreateDirectoryA(".\\EpochAdminToolLogs", NULL);
	
	char *p = strtok(function, "$$");

	// Check for file existance
	std::ifstream infile(".\\EpochAdminToolLogs\\Bases.sqf");
	bool fileExists = infile.good();

	// Create/open base txt
	std::ofstream myfile;
	myfile.open(".\\EpochAdminToolLogs\\Bases.sqf", std::ios_base::app);
	
	if (!fileExists) 
	{
		myfile << "=================================================================\n"
		       << "\t\t\t\tBase Exporter by NoxSicarius\n"
			   << "To use these bases navigate to base_manager.sqf, scroll to the\n"
			   << "bottom of the BCBaseList code block and follow the comments there.\n"
			   << "Remember to separate the bases by a comma as stated in the comments.\n"
			   << "=================================================================\n";
	}

	myfile << "\n\n\t\t\t/**************************************************\n"
		   << "\t\t\t\t\t\t\t Start of a new base\n"
		   << "\t\t\t**************************************************/\n\n\n";

	myfile << "\t[\n\t\t\"BASENAME\"//Name the base,\n"
		   << "\t\t\"DISPLAY NAME\"//give it a display name,\n"
		   << "\t\t[0,23,0], //This is the distance the base will spawn from you\n"
		   << "\t\t[\n";

	while (p)
	{
		myfile << "\t\t\t" << p << std::endl;
		p = strtok(NULL, "$$");
	}

	myfile << "\n\t\t]\n\t]\n\n\n";
	myfile.close();
}