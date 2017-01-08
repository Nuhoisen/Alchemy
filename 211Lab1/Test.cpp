/*************************************************************
*
* Lab/Assignment: Lab 1 – Alchemy Game
*
* Overview:
*	This program lets the user play a game of alchemy.
*	The game is simple.  The user is give a colored symbol, 
*	which they must place on the board.  However if the symbol
*	doesn't share a color or shape as neighboring symbols,
*	then it can't be placed. Bombs and free symbols have a 1/60 
*	chance to be generated through out the game. free symbols can
*	be placed anywhere. Bombs can remove any symbol. If the user
*	gets the highest recorded score in the game, then they 
*	can store their name in the records.
*	
*
* Input:
*	Symbols will be randomly generated which the user must 
*	place on the board.  They use the arrow keys to do this.
*
*	
*
* Output:
*	The board itself is the output, as well as the symbols and the
*	menu UI.  
*
************************************************************/

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "GameBoard.h"
#include "FileIO.h"
#include <iostream>

int main()
{
	srand(time(NULL));
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	

	GameBoard().GameFlow();

	return 0;


}

