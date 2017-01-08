/*
*Class: Gameboard
*
*	Purpose: This class creates the game board and handles the placement of symbols onto it.
*
*	Manager Functions:
*		FileIO(char * name): Default CTOR
*		~FileIO(): DTOR
*
*	Methods:
*		void WriteToFile(string * name): Function writes to text file
*	
*		string * ReadFromFile():		Function reads from text file
*/

#ifndef FILEIO
#define FILEIO
#include <fstream>
#include <iostream>
#include <string>
#include "Exception.h"
using std::cout;
using std::ofstream;
using std::ifstream;
using std::fstream;
using std::string;

class FileIO
{
public:

	FileIO(char * name);
	FileIO(const  FileIO & copy);
	FileIO & operator=(const FileIO & copy);
	~FileIO();

	void WriteToFile(string * name);
	string * ReadFromFile();

private:
	fstream mFile;
	string mNameList[4];
	string mFileName;
};


#endif // FILEIO