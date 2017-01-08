/*
* Class: Gameboard
*
* Purpose: This class creates the game board and handles the placement of symbols onto it.
*
* Manager Functions:
*		GameBoard();
*		GameBoard(char * fileName);
*		GameBoard(const GameBoard & copy);
*		GameBoard & operator=(const GameBoard & copy);
*		~GameBoard();
*
* Methods:
*
*		void CreateBoard(): This function creates the gameboard
*
*		bool LevelClear(): This function checks if the user has finished the game
*
*
*		int HomeScreen():	This function renders the homescreen for the user and returns theyre menu choice
*		int OptionsScreen(): This function renders the optionscreen and allows the user to select a difficulty
*
*
*		bool ColumnCheck(const COORD & lastCoord):  This function checks if columns are ready to be cleared
*		bool RowCheck(const COORD & lastCoord):		This function checks if rows are ready to be cleared
*
*		bool DumpPot(Symbol dumpSym):				This function fills and empties the cauldron
*		void ClearColumn(const COORD & cleanCoord):	This function clears the columns
*		void ClearRow(const COORD & cleanCoord):	This function clears the rows
*		void HighScoreScreen(): This function renders the highscore screen.
*		void Output(COORD startCoord, COORD finishCoord, Symbol symbol) :	This function outputs a symbol onto the
*		Symbol& GetNewSymbol(int difMod):			This function generates a new unique symbol:color type.
*		void GameFlow():							This function regulates where the user is directed once the game begins.
*		COORD & SetSymbol(int &difficulty)			This function sets the symbol onto the grid
*		bool SymbolCheck(Symbol& passed, COORD checkCord)	This function determines whether a symbol can be placed or not.
*		short BinaryTag(const COORD & checkCoord, int & wsOffSet)	This function is called by Symbol check to determine the current position of the symbol.
*
*		int CheckLeaderBoard():					This function checks if the users score is higher than the others.
*		void EnterName(int scoreIndex);
*		Array2D<Symbol> & getArray();
*/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "Array2D.h"
#include "KeyboardHandling.h"
#include "FileIO.h"
#include <Windows.h>
#include <wincon.h>
#include <stdlib.h>
#include <time.h>
#include <cctype>
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;


enum COLORS
{
	BLANK,
	BLUE,
	GREEN,
	TEAL,
	RED,
	PURPLE,
	YELLOW
};

//This structure represents a game piece.
//it consists of two attributes, color and symbolType
struct Symbol	
{
	char symbolType;
	int color;
};

const unsigned char V_LINE = 179;
const int GAMEBOUNDARY = 9;
const int CAULDRON_BOUNDARY = 4;
const int FULL_POT = 32;
const int EMPTY_POT = 33;
class GameBoard
{
public:
	
	GameBoard();
	GameBoard(char * fileName);
	GameBoard(const GameBoard & copy);
	GameBoard & operator=(const GameBoard & copy);
	~GameBoard();
	void CreateBoard();
	bool LevelClear();

	int HomeScreen();
	int OptionsScreen();
	bool ColumnCheck(const COORD & lastCoord);
	bool RowCheck(const COORD & lastCoord);	
	bool DumpPot(const Symbol &dumpSym);
	void ClearColumn(const COORD & cleanCoord);
	void ClearRow(const COORD & cleanCoord);
	void HighScoreScreen();
	void Output(COORD startCoord, COORD finishCoord, Symbol symbol);
	Symbol& GetNewSymbol(int difMod);
	void GameFlow();
	COORD & SetSymbol(int &difficulty);
	bool SymbolCheck(Symbol& passed, COORD checkCord);
	short BinaryTag(const COORD & checkCoord, int & wsOffSet);
	int CheckLeaderBoard();
	void EnterName(int scoreIndex);


private:
	char * mGameFileName;
	string * mFileContents;
	Array2D<Symbol> mPot;
	Array2D<Symbol> mGameGrid;	
	FileIO mGameFile;
	int mScore;


};
#endif // GAMEBOARD_H
