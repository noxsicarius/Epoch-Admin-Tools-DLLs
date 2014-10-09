// adminToolLog.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"

bool isStartup = true;

extern "C"
{
	__declspec(dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function);
}

void __stdcall RVExtension(char *output, int outputSize, const char *function)
{
	// Create folder if non-existant
	CreateDirectoryA(".\\EpochAdminToolLogs", NULL);

	// Open log file or create it
	std::ofstream myfile;
	myfile.open(".\\EpochAdminToolLogs\\AdminLog.txt", std::ios_base::app);

	// Get current date/time, format is YYYY-MM-DD HH:mm:ss
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);


	// Header for every server restart
	if (isStartup)
	{
		myfile << "\n\n=================================================================\n"
			   << "		Epoch Admin Tools Log Writer by NoxSicarius\n"
			   << "				Log for " << buf << "\n"
			   << "=================================================================\n\n";
		isStartup = false;
	}

	myfile << buf << " -- " << function << "\n";
	myfile.close();
}