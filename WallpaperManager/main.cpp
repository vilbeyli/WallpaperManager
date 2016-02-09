//////////////////////////////////////////////////////////////////////////
//
// Author	:	Volkan (Varaquilex) Ilbeyli
// Date		:	2/9/2016
// Purpose	:	From given directories for multiple monitor setups, to randomly
//				set a wallpaper in the directory for respective monitors
//
//////////////////////////////////////////////////////////////////////////

// cpp headers
#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::cout;
using std::endl;

int GetFileCountInDirectory(const string& dir = "")	// TODO: get file count in the given directory
{
	int fileCount = 0;
	// create the BAT file and execute it, write results to log.txt
	std::ofstream BATFile("FileCount.bat");
	if (BATFile.is_open())
	{
		// source: http://serverfault.com/a/111215
		BATFile << "set count=0 & for %%x in (*) do @(set /a count+=1 >nul)" << endl;
		BATFile << "echo %count%" << endl;
	}
	else
	{
		cout << "Error creating BAT file" << endl;
		return -1;
	}
	BATFile.close();
	system("FileCount.bat > log.txt");

	// open log.txt and parse it to get the file count
	std::ifstream logFile("log.txt");
	if (logFile.is_open())
	{
		string line;
		logFile.seekg(-9, std::ios_base::end);	// -9 is enough data for some reason "\r\n6\r\n6 echo"
		getline(logFile, line);

		logFile >> fileCount;
	}
	logFile.close();
	system("del FileCount.bat");
	system("del log.txt");

	return fileCount;
}

int main()
{
	int fileCount = GetFileCountInDirectory();
	
	cout << fileCount << endl;

	getchar();
	return 0;
}