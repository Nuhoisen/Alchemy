/*
*Author:			Kelly honsinger
*Filename:			Exception.cpp
*Date Created:		4/7/16
*Modifications:		4/10/16 Overloaded << operator.
*/
#include "Exception.h"


//default exception ctor
/***********************************************************************
* Purpose: This function is the default constructor. It sets
*			m_msg to base state or nullptr.
*
*
* Precondition: m_msg was uninitialized before call and therefore 
*			unknown.
*
* Postcondition:
*			m_msg is set to nullptr.
************************************************************************/
Exception::Exception(): m_msg(nullptr)
{}



//--------------------------------------------------------------------
//explicit exception ctor
/***********************************************************************
* Purpose: This function is the explict constructor. It sets
*			m_msg to a message that the user specifies.
*
*
* Precondition: m_msg was uninitialized before call and therefore
*			unknown.
*
* Postcondition:
*			m_msg is set to users desired message.  
*			Must be deallocated now.
************************************************************************/
Exception::Exception(char * msg)
{
	if (msg != nullptr)
	{
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
	else
		m_msg = nullptr;
}


//--------------------------------------------------------------------
//copy exception ctor
/***********************************************************************
* Purpose: This function is the copy  constructor. It sets
*			m_msg to the copies corresponding message
*			that the user passes.
*
*
* Precondition: m_msg was uninitialized before call and therefore
*			unknown.
*
* Postcondition:
*			m_msg is set to the copy's  message. It is a deep copy.
************************************************************************/
Exception::Exception(const Exception & copy)
{
	if (copy.m_msg != nullptr)
	{
		m_msg = new char[strlen(copy.m_msg) + 1];

		strcpy(m_msg, copy.m_msg);
	}
	else
		m_msg = nullptr;
}



//--------------------------------------------------------------------
//assignment Op
/***********************************************************************
* Purpose: This function is the assignment operator. It sets
*			m_msg to the copy that is passed.
*
*
* Precondition: m_msg is either known or unknown but is initialized.
*
* Postcondition:
*			m_msg is set to the copy's message. It is a deep copy.
*			It Must be deallocated now. 
************************************************************************/
Exception & Exception::operator=(const Exception & copy)
{
	if ((this != &copy) && (copy.m_msg!=nullptr))
	{
		delete[] m_msg;
		m_msg = new char[strlen(copy.m_msg) + 1];
		strcpy(m_msg, copy.m_msg);
	}
	return *this;
}



//--------------------------------------------------------------------
//get mutator
/***********************************************************************
* Purpose: This function is a getter. It returns a pointer to m_msg
*			The exceptions message.
*
*
* Precondition: Invoker must be initialized.  m_msg should probably not 
*			be null ptr since it will likely be used for output.
*
* Postcondition:
*			 No changes occur to invoking object.
************************************************************************/
const char * Exception::getMessage() const
{
	const char * tempMsg = m_msg;
	if (tempMsg == nullptr)
		tempMsg = "null msg";
	return tempMsg;
}



//--------------------------------------------------------------------
//set mutator
/***********************************************************************
* Purpose: This function is a setter. It changes the current m_msg member
*			to whatever is passed.
*
* Precondition: Invoker must be initialized.  m_msg can be null ptr since
*			it will be modified.
*
* Postcondition:
*		 m_msg will be allocated and set to passed message.  Must be
*		deallocated.	
************************************************************************/
void Exception::setMessage(char * message)
{
	if (message != nullptr)
	{
		delete[]m_msg;
		m_msg = new char[strlen(message) + 1];
		strcpy(m_msg, message);
	}
}



//--------------------------------------------------------------------
//cheveron overloaded operator

/***********************************************************************
* Purpose: This function is an overloaded chevron friend function. It is 
*			A friend function because it is invoked by the ostream class
*			(cout). it must be a friend for it to access the array's 
*			data members.
*
* Precondition: 
*			exception's m_msg can't be nullptr or else a default message will
*			be displayed.
* Postcondition:
*		 m_msg will be allocated and set to passed message.  Must be
*		deallocated.
************************************************************************/
ostream & operator<<(ostream & os,  const Exception & exception)
{
	if (exception.m_msg == nullptr)
	{
		os << "nullptr exception";
	}
	else
		os << exception.m_msg;
	return os;
}



//--------------------------------------------------------------------
//dtor
/***********************************************************************
* Purpose: This function is the exceptions destructor. It deallocates
*			m_msg's memory and sets it to nullptr.
*
* Precondition:
*			Exception object must be created for the destructor to be
*			called.
* Postcondition:
*		m_msg will be deleted and set to nullptr;
************************************************************************/
Exception::~Exception()
{
	delete[] m_msg;
	m_msg = nullptr;
	
}





