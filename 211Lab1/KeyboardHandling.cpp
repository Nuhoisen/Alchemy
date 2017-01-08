/*
*Author:			Kelly honsinger
*Filename:			KeyBoardHandling.cpp
*Date Created:		4/12/16
*Modifications:		None,		
*/
#include "KeyboardHandling.h"

//************************************************
/*KeyboardHandling::KeyboardHandling()
************************************************
*Purpose:   Default Ctor.
*
*Precondition:
*	Can be called from anywhere.
*
*Postcondition:
*	Object is created.
*/
KeyboardHandling::KeyboardHandling()
{
}

//************************************************
/*KeyboardHandling::KeyboardHandling(const KeyboardHandling & copy)
************************************************
*Purpose:   Copy Ctor.
*
*Precondition:
*	Can be called from anywhere.
*
*Postcondition:
*	Object is created.
*/
KeyboardHandling::KeyboardHandling(const KeyboardHandling & copy)
{}
//************************************************
/*KeyboardHandling & KeyboardHandling::operator=(const KeyboardHandling & copy)
************************************************
*Purpose:   Copy Ctor.
*
*Precondition:
*	Can be called from anywhere.
*
*Postcondition:
*	Object is created.
*/
KeyboardHandling & KeyboardHandling::operator=(const KeyboardHandling & copy)
{
	return *this;
}

//************************************************
/*KeyboardHandling::~KeyboardHandling()
************************************************
*Purpose:   Dtor
*
*Precondition:
*	Class exists.
*
*Postcondition:
*	Class doesn't exist.
*/
KeyboardHandling::~KeyboardHandling()
{
}
//************************************************
/*int KeyboardHandling::KeyPress()
************************************************
Purpose:   This function reads the users key presses and returns 
			an int associated to each key.

Precondition:
		Can be called from anywhere.

Postcondition:
		Int returned is one associated with the key that was pressed.
*/
int KeyboardHandling::KeyPress()
{

	DWORD        mode;
	HANDLE       hstdin;
	INPUT_RECORD inrec;
	DWORD        count;


	/* Set the console mode to no-echo, raw input, */
	/* and no window or mouse events.              */
	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hstdin == INVALID_HANDLE_VALUE || !GetConsoleMode(hstdin, &mode) || !SetConsoleMode(hstdin, 0))
	{
		return 0;
	}

	FlushConsoleInputBuffer(hstdin);

	/* Get a single key RELEASE */
	do
		ReadConsoleInput(hstdin, &inrec, 1, &count);
	while ((inrec.EventType != KEY_EVENT) || inrec.Event.KeyEvent.bKeyDown);


	SetConsoleMode(hstdin, mode);

	return inrec.Event.KeyEvent.wVirtualKeyCode;
}

//************************************************
/*COORD & KeyboardHandling::KeyHandler(COORD & currentCoord)
************************************************
*Purpose:   This function reads the users key presses and sets the cursor position
*			to the desired coordinate passed.  It is used to traverse around the game grid.
*
*Precondition:
*			Can be called from anywhere. Coordinate passed must be within the margin of the
*			console window.
*
*Postcondition:
*			Function only exits when the user presses the x or enter key.
*			These presses indicate either a caldron dump or symbol placement.
*/
COORD & KeyboardHandling::KeyHandler(COORD & currentCoord)
{
	short x = currentCoord.X;
	short y = currentCoord.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { ((x * 2) + 1), y });
	int i = 0;

	while ((i != VK_RETURN) && (i != X_KEY))//enter or x
	{
		i = KeyboardHandling().KeyPress();

		if (i == VK_UP)
		{
			if (y != 0)
			{
				y--;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { ((x * 2) + 1), y });
			}
		}

		if (i == VK_DOWN)
		{
			if (y != 8)
			{
				y++;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { ((x * 2) + 1), y });
			}

		}

		if (i == VK_LEFT)
		{
			if (x != 0)
			{
				x--;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { ((x * 2) + 1), y });
			}
		}

		if (i == VK_RIGHT)
		{
			if (x != 8)
			{
				x++;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { ((x * 2) + 1), y });
			}
		}

	}
	if (i == X_KEY)//x
		currentCoord.Y = 10;
	else
	{
		currentCoord.Y = y;
		currentCoord.X = x;
	}
	return currentCoord;
}