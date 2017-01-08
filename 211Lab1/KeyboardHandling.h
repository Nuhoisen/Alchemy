/*
*	Class: Gameboard
*
*	Purpose: This class manages the keyboard input of the game.  It does this by 
*			using a read console input function that repeated samples until a keypress
*			is found.
*
*	Manager Functions:
*	
*		KeyboardHandling();
*		~KeyboardHandling();
*	
*		TODO DO ASSIGN OP 
*		CTOR
*
*	Methods:
*		int KeyPress():		This function checks for a keypress and returns a
*							corresponding int value
*
*		COORD & KeyHandler(COORD & currentCoord): 	This function checks for 
*							the arrow key's and moves the cursor around.
*/
#ifndef KEYBOARDHANDLING_H
#define KEYBOARDHANDLING_H
#include <Windows.h>
const int X_KEY = 88;
class KeyboardHandling
{
public:
	KeyboardHandling();
	KeyboardHandling(const KeyboardHandling & copy);
	KeyboardHandling & operator=(const KeyboardHandling & copy);
	~KeyboardHandling();	


	int KeyPress();
	COORD & KeyHandler(COORD & currentCoord);
};
#endif // !KEYBOARDHANDLING
