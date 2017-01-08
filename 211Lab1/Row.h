/*
*Author:			Kelly Honsinger
*Filename:			Row.h
*Date Created:		4/3/16
*/
/************************************************************************
* Class: Row Template
*
* Purpose:	This class acts as a pivot class for ARRAY2D as it is needed
*			for overloading the double brackets operator.
*			It is called by the Array2D's bracket operator, where it 
*			then calls Array2D's select function. This allows it to return
*			The stored data.
*
* Manager Functions:
*			Row(const Array2D<T>& pArray, int row);
*			~Row();
*	
* Methods:
*			T & operator[](int column);
*			const T & operator[](int column)const;
*
*			const Array2D<T>&m_2Array;
*
************************************************************************/
#ifndef ROW_H_
#define ROW_H_


template <typename T> class Array2D;

template<typename T> class Row
{
public:
	Row(const Array2D<T>& pArray, int row);
	~Row();
	T & operator[](int column);
	const T & operator[](int column)const;

private:
	const Array2D<T>&m_2Array;
	int m_row;
};
/***********************************************************************
//EXPLICIT CTOR
/***********************************************************************
* Purpose: This function performs explicit initialization for the members
*			m_row and m_2array.  It is called from inside Array2D [] operator
*			function.  
*
* Precondition: m_length, m_start_index and m_array were uninitialized
*				before call and therefore unknown.
*
* Postcondition:
*			m_2array is passed an instance of it's calling calling class which i
*			it calls later.  m_row is set to the specified row.
************************************************************************/
template<typename T>
inline Row<T>::Row(const Array2D<T>& pArray, int row) :m_2Array(pArray), m_row(row)
{}

/***********************************************************************
//DTOR
/***********************************************************************
* Purpose: This function sets m_row to 0
*
* Precondition: object must exist to be destroyed.
*
* Postcondition: Object no longer exists.
*			
************************************************************************/
template<typename T>
inline Row<T>::~Row()
{
	m_row = 0;
}

//*********************************************************************
// Non- Const return
/***********************************************************************
* Purpose: This function is a non-constant bracket overloaded function.
*			it is called after array2d's bracket function.  It calls 
*			it's data member's m_2array function, select(m_row, column).
*
* Precondition: An instance of row must be created.  It is inaccessible from main
*				so it must be called by array2d's operator.
*
* Postcondition:
*			a non-constant value located at the specified index is returned.
************************************************************************/
template<typename T>
 T & Row<T>::operator[](int column) 
{
	return const_cast<Array2D<T> &>(m_2Array).Select(m_row, column);
}
 
 //*********************************************************************
 //const return
 /***********************************************************************
 * Purpose: This function is a non-constant bracket overloaded function.
 *			it is called after array2d's bracket function.  It calls
 *			it's data member's m_2array function, select(m_row, column).
 *
 * Precondition: An instance of row must be created.  It is inaccessible from main
 *				so it must be called by array2d's operator.
 *
 * Postcondition:
 *			a constant value located at the specified index is returned.
 ************************************************************************/
 template<typename T>
 const T & Row<T>::operator[](int column) const
 {
	 return m_2Array.Select(m_row, column);
 }

#endif // ROW_H_