#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_
#include <iostream>
#include <exception>
using namespace std;

class Exception 
{
private:
	char * m_msg;

public:
	Exception();
	Exception(char * msg);
	Exception(const Exception &copy);
	Exception& operator=(const Exception & copy);
	const char * getMessage() const;
	void setMessage(char * message);
	friend ostream& operator<<(ostream & os, const Exception & exception);
	~Exception();
};

#endif