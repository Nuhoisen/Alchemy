/*
*Class: Game board
*
*Purpose: This class creates the game board and handles the placement of symbols onto it.
*
*Manager Functions:
*	occf
*	Array2D():	Default CTOR
*	Array2D(int row, int column): Explicit CTOR
*	Array2D(const Array2D & copy): CTOR
*	Array2D& operator=(const Array2D & copy): Assignment Op
*	~Array2D(): D'tor
*
*Methods:
	Row<T> operator[] (int row): Index Operator.
	const Row<T> operator[] (int row)const: Const index operator
	int GetRow()const: Row Getter.
	void SetRow(int row): Row Setter.
	int GetColumn()const: Column Getter.
	void SetColumn(int col): Column Setter
	T & Select(int row, int col): Select function returns type.
	const T & Select(int row, int col)const: const select returns Type
*
*		
*/
#ifndef  ARRAY_2D_H_
#define ARRAY_2D_H_

#include "Row.h"
#include "Array.h"
template <typename T>
class Array2D
{

public:
	//occf
	Array2D();
	Array2D(int row, int column);
	Array2D(const Array2D & copy);
	Array2D& operator=(const Array2D & copy);
	~Array2D();

	//Functions
	Row<T> operator[] (int row);
	const Row<T> operator[] (int row)const;
	//mutators
	int GetRow()const;
	void SetRow(int row);
	int GetColumn()const;
	void SetColumn(int col);	
	T & Select(int row, int col);
	const T & Select(int row, int col)const;


private:
	Array<T> m_array;
	int m_row;
	int m_col;
};

//***********************************************************************
//Default CTOR
/***********************************************************************
* Purpose: This function performs default initialization for the members
*			m_array, m_row, and m_col of array template.
*			It assigns them to zero.
*
* Precondition: m_length, m_start_index and m_array were uninitialized
*				before call and therefor unknown.
*
* Postcondition:
*			Members m_row, M_col, m_array are set to zero.
************************************************************************/
template<typename T>
inline Array2D<T>::Array2D(): m_array(), m_row(0), m_col(0)
{}


//***********************************************************************
//Explicit Ctor
/***********************************************************************
* Purpose: This function performs explicit initialization for the members
*			m_row, m_col, and m_array of array template.
*			It assigns members m_row and m_col to the users
*			specifications and sends the product of the two to the 1D Array
			C'Tor.  It won't accept neg. lengths.
*
* Precondition: m_row, m_col and m_array were uninitialized
*				before call and therefore unknown.
*
* Postcondition:
*			Members m_row, m_col and m_array are set to
*			+positive user spec and [+user spec length]
*			respectively.
************************************************************************/
template<typename T>
inline Array2D<T>::Array2D(int row, int column): m_array(row*column), m_row(row), m_col(column)
{}


//********************************************************************
//Copy Ctor
/***********************************************************************
* Purpose: This function copies passed arrays members to the invoker's.
*			It assigns members m_array, m_row, and m_col to  the copy's
*			and allocates the same amount memory before copying over
*			the copy's array data. This is done in the Array class.
*
* Precondition: m_col, m_row, and m_array were uninitialized
*				before call and therefore unknown.
*
* Postcondition:
*			Members m_row, m_col and m_array are set to
*			copy.m_row, copy.m_col, copy.m_array,
*			respectively.
************************************************************************/
template<typename T>
inline Array2D<T>::Array2D(const Array2D & copy): m_array(copy.m_array), m_row(copy.m_row), m_col(copy.m_col)
{}


//***********************************************************************
//Assignment Operator
/***********************************************************************
* Purpose: This function copies passed arrays members to the invoker's.
*			It assigns members m_col and  m_row to  the copy's
*			and allocates the same amount memory before copying over
*			the copy's array data.
*
* Precondition: m_row, m_col and m_array were initialized before call.
*
* Postcondition:
*			Members m_col, m_row and m_array are set to
*			copy.m_col, copy.m_row, copy.m_array,
*			respectively.
************************************************************************/
template<typename T>
inline Array2D<T>& Array2D<T>::operator=(const Array2D & copy)
{
	if(this != &copy)
	{ 		
		m_array = copy.m_array;
		m_col = copy.m_col;
		m_row = copy.m_row;
	}
	return *this;
}

//***********************************************************************
//DTOR
/***********************************************************************
* Purpose: This function is the destructor.  It sets the Array2d's members
*			to their base state.
*
* Precondition:
*			Array2d Object must be created before it can be destroyed.
*			Default or non-default constructor will work.
*
*
* Postcondition:
*			m_row and m_col will be reinitialized
*			to default value, zero and zero.
************************************************************************/
template<typename T>
inline Array2D<T>::~Array2D()
{
	m_row = 0;
	m_col = 0;
}


//***********************************************************************
//overloaded index operator
/***********************************************************************
* Purpose: This function takes in a specified row index and returns a
*			row type that allows the proceeding index operator to be invoked.
*			This is because the second operator belongs to the row class which is being
*			returned. Array2d passes this pointer so that row can have an instance
*			for it to call the select function with.
*
* Precondition:
*			Array object must be initialized before it can be indexed.
*
* Postcondition:
*			If the passed index is positive and less than the row limit,
*			then a row object will be returned.  Otherwise an exception will
*			be thrown.
************************************************************************/
template<typename T>
inline Row<T> Array2D<T>::operator[](int specRow) 
{
	if ((specRow < m_row) && (specRow >= 0))
		return Row<T>(*this, specRow);
	else
		throw Exception("Invalid Row index\n");
}

//***********************************************************************
//constant overloaded index operator
/***********************************************************************
* Purpose: This function takes in a specified row index and returns a
*			row type that allows the proceeding index operator to be invoked.
*			This is because the second operator belongs to the row class which is being
*			returned. Array2d passes this pointer so that row can have an instance
*			for it to call the select function with.  Other note...It must be invoked
*			by a const object type other wise the non-const version will be called.
*
* Precondition:
*			Array object must be initialized before it can be indexed.
*
* Postcondition:
*			If the passed index is positive and less than the row limit,
*			then a row object will be returned.  Otherwise an exception will
*			be thrown.
************************************************************************/
template<typename T>
inline const Row<T> Array2D<T>::operator[](int specRow) const
{
	if ((specRow < m_row) && (specRow >= 0))
		return Row<T>(*this, specRow);
	else
		throw Exception("Invalid Row index\n");
}



//***********************************************************************
//mutator returns row number
/***********************************************************************
* Purpose: This function returns the number of rows. It is constant
*			because it shouldn't be modified. It should just be returned.
*
* Precondition:
*			Array object must be initialized before it can have an index
*			returned. Default or non-default constructor will work.
*
* Postcondition:
*			No change to object.
************************************************************************/
template<typename T>
inline int Array2D<T>::GetRow() const
{
	return m_row;
}


//***********************************************************************
//mutator sets the row number
/***********************************************************************
* Purpose: This function sets the number of rows. if the value is being 
*			reduced, then the array will pass (m_row * m_col) - cutOff 
*			into it's reset function. Otherwise, (m_col*row) is the new 
*			value passed.
* Precondition:
*			Array object must be initialized before it can have an index
*			returned. Default or non-default constructor will work.
*
* Postcondition:
*			Row is either expanded or shrunken. Data will be left alone unless
*			it exceeds the new bounds.
************************************************************************/
template<typename T>
inline void Array2D<T>::SetRow(int row)
{
	if (row > 0 && row < m_row)
	{
		m_row = row;
		int cutOff= m_row - row;
		cutOff = cutOff * m_col;
		m_array.setLength((m_row * m_col) - cutOff);
	}
	else if (row >= m_row)
	{
		m_row = row;
		m_array.setLength(m_row * m_col);

	}
	else if (row == 0)
	{
		m_row = row;
		m_array.setLength(row);
	}

	else
	{
		throw Exception("Can't specify negative row\n");
	}
}


//***********************************************************************
//mutator gets the column val
/***********************************************************************
* Purpose: This function returns the number of columns. It is constant
*			because it shouldn't be modified. It should just be returned.
*
* Precondition:
*			Array object must be initialized before it can have an index
*			returned. Default or non-default constructor will work.
*
* Postcondition:
*			No change to object.
************************************************************************/
template<typename T>
inline int Array2D<T>::GetColumn() const 
{
	return m_col;
}


//***********************************************************************
//mutator sets the column number										
/***********************************************************************
* Purpose: This function sets the number of columns. It uses
*			overly complex algorithms to shift that data inside the array
*			appropriately.
*
* Precondition:
*			Array object must be initialized before it can be set
*			Default or non-default constructor will work.
*
* Postcondition:
*			Column axis is either expanded or shrunken. Data will be left alone unless
*			it exceeds the new bounds.
************************************************************************/																	
template<typename T>
inline void Array2D<T>::SetColumn(int col)
{
	if ((col > 0) && (col < m_col))
	{
		int temp = col;
		col= m_col - col;//chop off amount
		for (int i = 1; i < m_row; i++)//i reps rows
		{
			for (int j = 0; j < temp; j++)	//col vals
				m_array[(m_col * i) - (i* col) + j] = m_array[(m_col* i) + j];
		}
		m_col = temp;
		m_array.setLength(m_col * m_row);
	}
	else if (col > m_col)
	{
		int temp = col;
		col =  col- m_col;

		m_array.setLength(temp * m_row);
		Array<T> tempArray = m_array;
		
		for (int i = 1; i < m_row; i++)//i reps rows
		{
			for (int j = 0; j < m_col; j++)	//col vals
				m_array[(temp * i) + j] = tempArray[(m_col * i)+ j];
		}
		m_col = temp;
	}

	else if (col == 0)
	{
		m_array.setLength(col);
		m_col = col;
	}

	else if (col == m_col)
	{
		m_col = col;
	}
	else
	{
		throw Exception("Can't set a column length less than zero\n");
	}
}

//***********************************************************************
//select function
/***********************************************************************
* Purpose: This function is called by the row class from inside its 
*			overloaded index operator function.  It returns an index 
*			from the 1D array that is equal to (original col * spec_row)+(spec_col)
*
* Precondition:
*			Array object must be initialized before it can be selected from indexing.
*			Default or non-default constructor will work.
*
* Postcondition:
*			Data is returned if the indices aren't out of bounds.
*			Otherwise an exception is thrown.
************************************************************************/
template<typename T>
inline T & Array2D<T>::Select(int row, int col)
{
	if ((col< m_col) && (col>=0))
		return m_array[(m_col*row)+(col)];
	
	else throw Exception("Invalid Column index");
}


//***********************************************************************
//const select function
/***********************************************************************
* Purpose: This function is called by the row class from inside its
*			overloaded index operator function.  It returns an index
*			from the 1D array that is equal to (original col * spec_row)+(spec_col).
*			It is called by the const class member inside the row class.
*
* Precondition:
*			Array object must be initialized before it can be selected from indexing.
*			Default or non-default constructor will work.
*
* Postcondition:
*			Data is returned if the indices aren't out of bounds.
*			Otherwise an exception is thrown.
************************************************************************/
template<typename T>
const T & Array2D<T>::Select(int row, int col) const
{
	if ((col < m_col) && (col >= 0))
		return m_array[(m_col*row) + (col)];
	
	else throw Exception("Invalid Column index");
}
#endif