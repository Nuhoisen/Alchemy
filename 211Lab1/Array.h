/************************************************************************
* Author:			Kelly Honsinger
* Filename:			Array.h
* Date Created:		3/28/2016
* Modifications:	3/29/2016-	Implemented throw operations.
* 
************************************************************************/
#ifndef _ARRAY_H_
#define _ARRAY_H_
#include "Exception.h"

/************************************************************************
* Class: Array Template
*
* Purpose:	This class is a templated array type that can hold various 
* data types. It overloads the bracket operation to assign values
* to itself. 
*
* Manager Functions: 
*		Array() 
*			Default constructor: Default length is zero, and default
*			base is zero.
*		
*		Array(int length, int start_index = 0)
*			Explicit constructor: length is set by user, and start_index
*			is set by user or else just zero by default.
*		
*		Array (const Array & copy)
*			Copy constructor: length, base, and array, are set by 
*			copy that is passed.
*		
*		operator= (const Array & copy)
*			assignment operator: length and base are reset, array is
*			deleted, and then all are reassigned to the copy.
*
*		int getStartIndex()
*			Mutator: getter for base index.
*		void setStartIndex(int startIndex)
*			Mutator: setter for base index.
*			

************************************************************************/


template <typename T>
class Array
{
private:
	int m_length;
	int m_start_index;
	T * m_array;

public:
	Array();									//DEFAULT CTOR
	Array(int length, int start_index = 0);		//PARAM CTOR			
	Array(const Array &cArray);					//COPY CTOR
	Array & operator = (const Array &cArray);	//ASSIGN OP
	
	T & operator[](int index)const;				//receive and modify index
	//MUTATORS
	int getStartIndex();						//gets start index
	void setStartIndex(int startIndex);			//sets start index

	int getLength();							//return length
	void setLength(int length);					//set + length

	~Array();									//DTOR

};


/***********************************************************************
* Purpose: This function performs default initialization for the members
*			m_length, m_start_index, and m_array of array template. 
*			It assigns them to zero and null.
*
* Precondition: m_length, m_start_index and m_array were uninitialized
*				before call and therefor unknown.
*
* Postcondition: 
*			Members m_length, m_start_index and m_array are set to
*			0, 0, and nullptr, respectively.
************************************************************************/
template<typename T>
inline Array<T>::Array(): m_length(0), m_start_index(0), m_array(nullptr)
{}


//-----------------------------------------------------------------------

//EXPLICIT CTOR


/***********************************************************************
* Purpose: This function performs explicit initialization for the members
*			m_length, m_start_index, and m_array of array template.
*			It assigns members m_length and m_start_index to the users
*			specifications and allocates enough memory to accommodate for
*			the specified length.  It won't accept neg. lengths.
*
* Precondition: m_length, m_start_index and m_array were uninitialized
*				before call and therefore unknown.
*
* Postcondition:
*			Members m_length, m_start_index and m_array are set to
*			+positive user spec, user spec, and [+user spec length]
*			respectively.
************************************************************************/

template<typename T>
inline Array<T>::Array(int length, int start_index) : m_length(length), m_start_index(start_index)
{
	//EXCEPTION HERE: Negative length
	if (m_length < 0)
	{
		throw Exception("Cannot specify neg. length in c'tor\n");
	}

	m_array = new T[m_length];
	//set base  members to zero
}



//----------------------------------------------------------------------------

//Copy CTOR
/***********************************************************************
* Purpose: This function copies passed arrays members to the invoker's.
*			It assigns members m_length and m_start_index to  the copy's
*			and allocates the same amount memory before copying over
*			the copy's array data. 
*
* Precondition: m_length, m_start_index and m_array were uninitialized
*				before call and therefore unknown.
*
* Postcondition:
*			Members m_length, m_start_index and m_array are set to
*			copy.m_length, copy.m_start_index, copy.m_array,
*			respectively.
************************************************************************/

template<typename T>
inline Array<T>::Array(const Array & cArray) : m_length (cArray.m_length), m_start_index(cArray.m_start_index)
{
	m_array = new T[m_length];

	for (int i = 0; i < m_length; i++)	
		m_array[i] = cArray.m_array[i];

}


//----------------------------------------------------------------------------


//Assign OP

/***********************************************************************
* Purpose: This function copies passed arrays members to the invoker's.
*			It assigns members m_length and m_start_index to  the copy's
*			and allocates the same amount memory before copying over
*			the copy's array data.
*
* Precondition: m_length, m_start_index and m_array were either known or
*			unknown but initialized before call.
*
* Postcondition:
*			Members m_length, m_start_index and m_array are set to
*			copy.m_length, copy.m_start_index, copy.m_array,
*			respectively.
************************************************************************/
template<typename T>
inline Array<T> & Array<T>::operator=(const Array & copy)
{
	if (this != &copy)									//if array is being assigned to itself, just return it
	{
		delete[] m_array;								//delete what array was pointing to originally
		m_length = copy.m_length;
		m_start_index = copy.m_start_index;

		m_array = new T[m_length];						//create new allocated array

		for (int i = 0; i < m_length; i++)
		{
			m_array[i] = copy.m_array[i];				//m_start_index
		}
	}
	return *this;
}


//------------------------------------------------------------------

//Returns value at location and overwrites it

/***********************************************************************
* Purpose: This function takes in a specified int index and returns a
*			corresponding value at that index or else throws an exception
*			as it is otherwise out of bounds.
*
* Precondition: 
*			Array object must be initialized before it can be indexed.
*			
* Postcondition:
*			values can be assigned to the specified indexed position, 
*			which can modify the array. Otherwise it will just return
*			the value at the specified index
************************************************************************/
template<typename T>
inline T & Array<T>::operator[](int index)const
{	//EXCEPTION HERE: INVALID INDEX PASS
	if ((index < m_start_index) || (index >(m_length + m_start_index)))
		throw Exception("invalid index; outside of scope!\n");
	
	return m_array[index - m_start_index];
}

//--------------------------------------------------------------------

//returns starting index
/***********************************************************************
* Purpose: This function returns a the starting index value
*
* Precondition:
*			Array object must be initialized before it can have an index 
*			returned. Default or non-default constructor will work.
*
* Postcondition:
*			No change to object.
************************************************************************/
template<typename T>
inline int Array<T>::getStartIndex()
{
	return m_start_index;
}

//--------------------------------------------------------------------

//sets starting index
/***********************************************************************
* Purpose: This function changes the starting index value to the user's 
*			desired index.
*
* Precondition:
*			Array object must be initialized before it can have an index
*			modified. Default or non-default constructor will work.
*			Set index can be positive or negative
*
* Postcondition:
*			No change to object.
************************************************************************/
template<typename T>
inline void Array<T>::setStartIndex(int startIndex)
{	
	m_start_index = startIndex;
}


//-------------------------------------------------------------------------

//returns array length
/***********************************************************************
* Purpose: This function returns the set length of the array.
*
* Precondition:
*			Array object must be initialized before it can have an index
*			modified. Default or non-default constructor will work.
*			
*
* Postcondition:
*			No change to object.
************************************************************************/
template<typename T>
inline int Array<T>::getLength()
{
	return m_length;
}


//-----------------------------------------------------------------------

//Set Length
//sets starting index
/***********************************************************************
* Purpose: This function changes the length of the array 
*			value to the user's	desired length.  It will either expand 
*			or truncate the array.  
*
* Precondition:
*			Array object must be initialized before it can have an index
*			modified. Default or non-default constructor will work.
*			Set length can be higher than or lower than the current length
*			but it must be positive.  It can be set to zero.
*
* Postcondition:
*			Array data is transferred into a temp array before being 
*			transferred back into modified array.  Data that lies outside
*			the new boundaries will be lost.
************************************************************************/
template<typename T>
inline void Array<T>::setLength(int length)
{	//EXCEPTION HERE: Negative Length
	if (length < 0)
	{
		Exception e;
		throw e;
	}
	
	
	int set_Length = (length >= m_length) ? m_length : length;		//if the array is being shrunk, then the temp size must be the 
		
	T * tempArray = new T[set_Length];
	for (int i = 0; i < set_Length; i++)
	{
		tempArray[i] = m_array[i];
	}
		
	delete[] m_array;
		
	m_array = new T[length];
		
	for (int i = 0; i < set_Length; i++)
	{
		m_array[i] = tempArray[i];
	}

	m_length = length;

	delete[] tempArray;

}

//---------------------------------------------------------------------

//D'TOR
/***********************************************************************
* Purpose: This function is the destructor.  It deallocates any
*			allocated array memory and then sets it and other
*			the data members to their base states.  
*
* Precondition:
*			Array Object must be created before it can be destroyed.
*			Default or non-default constructor will work.
*			
*
* Postcondition:
*			Array data deleted and then the pointer will be reinitialized
*			to nullptr.   m_length and m_start_index will be reinitialized 
*			to default value, zero and zero.
************************************************************************/
template<typename T>
inline Array<T>::~Array()
{
	delete[] m_array;
	m_array = nullptr;

	m_start_index = 0;
	m_length = 0;
}

#endif // !_ARRAY_H_