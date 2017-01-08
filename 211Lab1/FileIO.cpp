/*
*Author:			Kelly Honsinger
*Filename:			FileIO.cpp
*Date Created:		4/13/16
*Modifications:		4/13/16 Struggled
*					4/13/16 No mem leaks!
*/
#include "FileIO.h"
/* FileIO::FileIO(char * name)
*Purpose: Constructor takes in file name, attempts to open file, and does a file check.
*
*Precondition:	File must exist or be able to be created. Else an exception will be thrown.
*
*Postcondition: File will either be opened or exception will be thrown
*/

FileIO::FileIO(char * name) : mNameList{}, mFileName(name)
{
	mFile.open(name);
	if (mFile.fail())
	{
		throw Exception("Unable To open File");
	}	
}

FileIO::FileIO(const FileIO & copy)
{
	mFile.open(copy.mFileName);
	if (mFile.fail())
	{
		throw Exception("Unable To open File");
	}
}

FileIO & FileIO::operator=(const FileIO & copy)
{
	if (this!= &copy)
		mFile.open(copy.mFileName);
	if (mFile.fail())
	{
		throw Exception("Unable To open File");
	}
	return *this;
}

/* FileIO::~FileIO()
*Purpose: Destructor.
*
*Precondition:	FileIo object must exist.
*
*Postcondition: FileIo won't exist.
*/
FileIO::~FileIO()
{
	if (mFile.is_open())
	{
		mFile.close();
	}
}

/* void FileIO::WriteToFile(string * name)
*Purpose: Function used to write to specified file name.
*				It will write the contents of a string array to the file, inserting newline
*				between each element in  the array.
*
*Precondition:	String must consist of data to be written for any effect to
*				take place.
*
*Postcondition: Existing file will be overwritten with new data.
*/
void FileIO::WriteToFile(string * name)
{
	int i = 0;

	ofstream fout;
	
	fout.open(mFileName);
	if (!fout.fail())
	{
		while ((!name[i].empty()) && (i < 4))
		{
			fout << name[i] << "\n";
			i++;
		}
		fout.close();
	}
}

/* string * FileIO::ReadFromFile()
*Purpose: This function reads the data from the file into a string array.
*				The string array is then returned to the caller to use.
*
*Precondition:	File must exist for any data to be read.
*
*Postcondition: Return string array will hold each line of the file in 
*				it's elements.
*/
string * FileIO::ReadFromFile()
{
	const int MAX = 40;
	string buffer;
	ifstream fin;
	
	fin.open(mFileName);
	
	if (!fin.fail())
	{
		for (int i = 0; i < 4; i++)
		{

			if (fin.peek() != std::ifstream::traits_type::eof())
			{
				getline(fin, buffer);
				mNameList[i] = buffer;
			}
		}
		fin.close();
	}
	return mNameList;
}

