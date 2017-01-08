/*
*Author:			Kelly honsinger
*Filename:			GameBoard.cpp
*Date Created:		4/7/16
*Modifications:		4/10/16 added bombs
*					4/11/16 added wildflag
*/
#include "GameBoard.h"



//----------------------------------------------------------------------------
//Default CTOR
/***********************************************************************
* Purpose: This function acts as the games default ctor. It sets up the
*			Grid Dimensions, the pot dimensions, and the leaderFile.
*
* Precondition: mGameGrid, mPot, mScore, mGameFile, mGameFileName, and
*				mFileContents were uninitialized before call and therefore unknown.
*
* Postcondition:
*			Members mGameGrid, mPot, mScore, mGameFile, mGameFileName,and
*			mFileContents are set to (10,10), (1, 5), 0, leaderFile.txt, and mGameFileName respectively.
************************************************************************/
GameBoard::GameBoard() : mGameGrid(10, 10), mPot(1, 5), mScore(0), mGameFileName("leaderFile.txt"), mGameFile(mGameFileName)
{
	mFileContents = mGameFile.ReadFromFile();

	for (int i = 9; i < 10; i++)			//initialize boundaries to 0
	{
		for (int j = 0; j < 10; j++)
		{
			mGameGrid[i][j].symbolType = 0;
			mGameGrid[j][i].symbolType = 0;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		mPot[0][i].color = 0;
		mPot[0][i].symbolType = 0;
	}
}


//----------------------------------------------------------------------------
//Explicit CTOR
/***********************************************************************
* Purpose: This function acts as the games explicit ctor. It sets up the
*			Grid Dimensions, the pot dimensions, and the leaderFile. It takes in
*			A user defined gamefile name.
*
* Precondition: mGameGrid, mPot, mScore, mGameFile, mGameFileName, and
*				mFileContents were uninitialized before call and therefore unknown.
*
* Postcondition:
*			Members mGameGrid, mPot, mScore, mGameFile, mGameFileName,and
*			mFileContents are set to (10,10), (1, 5), 0, fileName, and mGameFileName respectively.
************************************************************************/
GameBoard::GameBoard(char * fileName) : mGameGrid(10, 10), mPot(1, 5), mScore(0), mGameFileName(fileName), mGameFile(mGameFileName)
{
	mFileContents = mGameFile.ReadFromFile();

	for (int i = 9; i < 10; i++)			//initialize boundaries to 0
	{
		for (int j = 0; j < 10; j++)
		{
			mGameGrid[i][j].symbolType = 0;
			mGameGrid[j][i].symbolType = 0;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		mPot[0][i].color = 0;
		mPot[0][i].symbolType = 0;
	}
}

//----------------------------------------------------------------------------
//Copy CTOR
/***********************************************************************
* Purpose: This function copies passed Gameboard's members to the invoker's.
*			It assigns members mGameGrid, mPot, mScore, mGameFile, mGameFileName,
*			and mFileContents to the copy's.
*
* Precondition: mGameGrid, mPot, mScore, mGameFile, mGameFileName, and
*				mFileContents were uninitialized before call and therefore unknown.
*
* Postcondition:
*			Members mGameGrid, mPot, mScore, mGameFile, mGameFileName,and
*			mFileContents are set to copy.mGameGrid, copy.mPot, copy.mScore,
*			copy.MGameFile, copy.mGameFileName, and copy. mFileContents respectively.
************************************************************************/
GameBoard::GameBoard(const GameBoard & copy) : mGameGrid(copy.mGameGrid), mPot(copy.mPot), mScore(copy.mScore), mGameFileName(copy.mGameFileName), mGameFile(copy.mGameFile), mFileContents(copy.mFileContents)
{}

//----------------------------------------------------------------------------
//Assignment OP
/***********************************************************************
* Purpose: This function copies passed Gameboard's members to the invoker's.
*			It assigns members mGameGrid, mPot, mScore, mGameFile, mGameFileName,
*			and mFileContents to the copy's.
*
* Precondition: mGameGrid, mPot, mScore, mGameFile, mGameFileName, and
*				mFileContents were initialized before call.
*
* Postcondition:
*			Members mGameGrid, mPot, mScore, mGameFile, mGameFileName,and
*			mFileContents are set to copy.mGameGrid, copy.mPot, copy.mScore,
*			copy.MGameFile, copy.mGameFileName, and copy. mFileContents respectively.
************************************************************************/
GameBoard & GameBoard::operator=(const GameBoard & copy)
{
	if (this != &copy)
	{
		mScore = copy.mScore;
		mFileContents = copy.mFileContents;
		mGameFileName = copy.mGameFileName;
		mPot = copy.mPot;
		mGameGrid = copy.mGameGrid;
		mGameFile = copy.mGameFile;
	}

	return *this;
}

//----------------------------------------------------------------------------
//DTOR
/***********************************************************************
* Purpose: This function is a destructor for passed Gameboard's members.
*			It sets members mGameGrid, mPot, mScore, mGameFile, mGameFileName,
*			and mFileContents to zero or nullptr.
*
* Precondition: An instance of Gameboard must exist for the destructor to call.
*
* Postcondition:
*			Members mGameGrid, mPot, mScore, mGameFile, mGameFileName,and
*			mFileContents are set to zero or nullptr.
************************************************************************/
GameBoard::~GameBoard()
{
	mScore = 0;
	mFileContents = nullptr;
	mGameFileName = nullptr;
	for (int i = 0; i < 10; i++)			//initialize boundaries to 0
	{
		for (int j = 0; j < 10; j++)
		{
			mGameGrid[i][j].symbolType = 0;
			mGameGrid[i][j].color = 0;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		mPot[0][i].color = 0;
		mPot[0][i].symbolType = 0;
	}
}


/* void GameBoard::GameFlow()
Purpose: This function renders the homescreen and then calls the keyboard handling class
to determine the users desired option.  It then redirects the user to their selected option.

Precondition:	A game instance must be created to call this function.

Postcondition:	The user can only exit this function by calling the exit option.*/

void GameBoard::GameFlow()
{
	int gameOpt= 0;
	int difficulty = 0;
	int leaderTrack = 0;

	Symbol dumpster = { EMPTY_POT, 0 };		//empty cauldron key
	while (gameOpt != 3)
	{
		system("cls");
		gameOpt = HomeScreen();


		if (gameOpt == 0)
		{
			CreateBoard();
			bool gameOver = false;
			COORD returnCoord;


			while (!gameOver)
			{
				returnCoord = SetSymbol(difficulty);
				if (returnCoord.X < 10)
				{
					if (ColumnCheck(returnCoord))		//assign ints to these so that we can do col and row checks before
					{
						ClearColumn(returnCoord);
					}

					else if (RowCheck(returnCoord))
					{
						ClearRow(returnCoord);
					}

					gameOver = LevelClear();
				}
				else if (returnCoord.X == 11)
				{
					gameOver = true;
				}
			}

			leaderTrack = CheckLeaderBoard();
			if (leaderTrack < 4)
			{
				EnterName(leaderTrack);
			}
		
			DumpPot(dumpster);
			mScore = 0;
		}
		else if (gameOpt == 1)
		{
			HighScoreScreen();
		}

		else if (gameOpt == 2)
		{
			difficulty = OptionsScreen();
		}
	}
}

/* int GameBoard::HomeScreen()
Purpose: This function renders the home screen and handles the user input by responding
to the arrow and enter keys.  

Precondition:	The function must be called form the gameplay function and therefor
must have a game instancce created beforehand.

Postcondition: The function will return an int and depending on what option the user
selected. */

int GameBoard::HomeScreen()
{
	COORD homeCOORD = { 0, 2 };
	int i = 0;		//i is the virtual keyboard return value.
	char * currentPtr;
	
	char * title = "Alchemy";
	char * newGame = "Start New Game";
	char * options = "Options";
	char * quit = "Quit";
	char * hiScore = "High Scores";

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),  homeCOORD);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	
	cout << title << endl << endl << endl;
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x9F);
	cout << newGame << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	cout << hiScore << endl << endl;
	cout << options<<endl<<endl;
	cout << quit << endl << endl;


	homeCOORD = { 0, 5 };
	currentPtr = newGame;

	while (i != 13)
	{
		i = KeyboardHandling().KeyPress();
		
		if (i == VK_UP)
		{
			if (currentPtr == hiScore)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
				cout << hiScore;

				homeCOORD.Y -= 2;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x9E);
				cout << newGame;
				currentPtr = newGame;
			}

				
			else if (currentPtr == options)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
				cout << options;

				homeCOORD.Y -= 2;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x9E);
				cout << hiScore;
				currentPtr = hiScore;
			}
			else if (currentPtr == quit)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
				cout << quit;

				homeCOORD.Y-=2;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x9E);
				cout << options;
				currentPtr = options;
			}
			
		}
		else if (i == VK_DOWN)
		{
			if (currentPtr == newGame)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
				cout << newGame;

				homeCOORD.Y += 2;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x9E);
				cout << hiScore;
				currentPtr = hiScore;
			}

			else if (currentPtr == hiScore)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
				cout << hiScore;

				homeCOORD.Y += 2;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x9E);
				cout << options;
				currentPtr = options;
			}

			else if (currentPtr == options)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
				cout << options;

				homeCOORD.Y += 2;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x9E);
				cout << quit;
				currentPtr = quit;
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);

	if (currentPtr == newGame)
		i = 0;
	else if (currentPtr == hiScore)
		i = 1;
	
	else if (currentPtr == options)
		i = 2;
	else	//quit
		i = 3;

	return i;
}


/* void GameBoard::HighScoreScreen()
Purpose: This function renders the highscore SCREEN.

Precondition:	The function must be called form the gameplay function and therefor
must have a game instancce created beforehand.

Postcondition: The function will return an int and depending on what option the user
selected. */
void GameBoard::HighScoreScreen()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	cout << "HIGH SCORES\n____________\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	int i = 0;

	mFileContents = mGameFile.ReadFromFile();
	for (int i = 0; i < 4; i++)
	{
		cout << i + 1 << "." << mFileContents[i] << endl << endl;
	}
	

	int vkValue=0;
	while ((vkValue != 13) && (vkValue != VK_ESCAPE))
		vkValue = KeyboardHandling().KeyPress();
}


/* int GameBoard::OptionsScreen()
Purpose: This function renders the options screen which allows the user to select
 levls of difficulty.

Precondition:	The  game sets its difficulty to easy by default, soif the user wants to
change the difficulty, they will change it to hard.

Postcondition: The function returns an int depending on what option they selected. */
int GameBoard::OptionsScreen()
{
	system("cls");
	COORD homeCOORD = { 10, 3 };
	int i = 0;
	char * currentPtr;

	char * easy = "EASY";
	char * hard = "HARD";


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {homeCOORD});
	cout << hard;

	homeCOORD.X -= 8;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x9E);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
	cout << easy;


	currentPtr = easy;

	while ((i != VK_RETURN) && (i != VK_ESCAPE))
	{
		i = KeyboardHandling().KeyPress();

		if (i == VK_RIGHT)
		{

			if (currentPtr == easy)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
				cout << easy;

				homeCOORD.X += 8;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x9E);
				cout << hard;
				currentPtr = hard;
			}
		}
		else if (i == VK_LEFT)
		{
			if (currentPtr == hard)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
				cout << hard << (char) 32;//ADD a space maybe?

				homeCOORD.X -= 8;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCOORD);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x9E);
				cout << easy;
				currentPtr = easy;
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);

	if (currentPtr == easy)
		i = 0;
	else
		i = 1;

	return i;
}


/*void GameBoard::CreateBoard()
Purpose: This function renders the gameboard and it's features.

Precondition:  This function must be called by the home screen menu, so the user must 
choose to start the game. 

Postcondition: Calling the function will send the user into a loop that runs the game.
In addition the original homescreen will be replaced with a grid interface screen. */
void GameBoard::CreateBoard()//start position, 
{
	system("cls");

	Symbol setUp = { (char)254, BLANK };

	
	COORD start = { 0, 0 };
	COORD finish = { 9,3 };	
	Output(start, finish, setUp);

	start = { 0, 3 };
	finish = { 4,4 };
	Output(start, finish, setUp);

	start = { 4, 3 };
	finish = { 5, 4 };

	setUp.symbolType = 35;	
	Output(start, finish, setUp);
	
	start = { 5, 3 };
	finish = { 9, 4 };

	setUp.symbolType = (char)254;
	Output(start, finish, setUp);
	
	start = { 0, 4 };
	finish = { 9, 9 };
	Output(start, finish, setUp);

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 18, 0 });
	for (int i = 0; i < 9; i++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 18, (short)i });
		cout << "|" << (i );
		
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 9 });
	for (int i = 0; i < 9; i++)
	{
		cout << "|" << i;
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 25, 2 });
	cout << "CAULDRON";

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 25, 3 });

	cout <<(char) 218 << "-----"<< (char)191;
	

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 25, 3 });
	for (short i = 4; i < 5; i++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 25, i });
		cout << (char)179;
	}

	for (short i = 4; i < 5; i++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 31, i });
		cout << (char)179;
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 25, 5 });
	cout << (char)192 << "-----" << (char)217;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 26, 7 });
	cout << "SCORE";
}


/*bool GameBoard::LevelClear()
Purpose: This function runs after the user has placed a piece. It checks
if all of the squares on the grid have been cleared.  It returns a bool confirming
or rejecting the case.

Precondition:  THis function runs after the user has successfully placed a piece onto the 
board.  

Postcondition:  This function determines whether the game is over or not.  If false, the game flow
will continue, otherwise it will terminate. */
bool GameBoard::LevelClear()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			if (mGameGrid[i][j].symbolType == -2)
				return false;
	}

	return true;
}

/*bool GameBoard::ColumnCheck(const COORD & lastCoord)
Purpose: This function runs after the user has placed a piece. It checks
if a column has been successfully cleared.

Precondition:  THis function runs after the user has successfully placed a piece onto the
board.

Postcondition:  This function determines whether to clear a column or not. If it returns true, it will clear
open up space for the user on the board. If false, it will do nothing*/
bool GameBoard::ColumnCheck(const COORD & lastCoord)
{
	for (int i = 0; i < 9; i++)
	{
		if ((mGameGrid[lastCoord.X][i].symbolType == -2) || (mGameGrid[lastCoord.X][i].symbolType == -80 ))
			return false;
	}

	return true;
}


/*bool GameBoard::RowCheck(const COORD & lastCoord)
Purpose: This function runs after the user has placed a piece. It checks
if a row has been successfully cleared.

Precondition:  THis function runs after the user has successfully placed a piece onto the
board.

Postcondition:  This function determines whether to clear a row or not. If it returns true, it will clear
open up space for the user on the board. If false, it will do nothing*/
bool GameBoard::RowCheck(const COORD & lastCoord)
{

	for (int i = 0; i < 9; i++)
	{
		if ((mGameGrid[i][lastCoord.Y].symbolType == -2) || (mGameGrid[i][lastCoord.Y].symbolType == -80))
			return false;
	}
	return true;
}


/*void GameBoard::ClearRow(const COORD & cleanCoord)
Purpose: This function runs after row check has returned true.  It is passed
a coordinate of the lowest column index corresponding to that row.

Precondition:  THis function runs after the user has successfully placed a piece onto the
board.

Postcondition:  This function determines whether to clear a row or not. If it returns true, it will clear
open up space for the user on the board. If false, it will do nothing*/
void GameBoard::ClearRow(const COORD & cleanCoord)
{
	char ClearSym = 176;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (short i = 0; i < 9; i++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (i*2) , cleanCoord.Y});
		cout << '|';
		cout << ClearSym;
		mGameGrid[i][cleanCoord.Y].symbolType = ClearSym;
		mGameGrid[i][cleanCoord.Y].color = 0;
	}
}


/*void GameBoard::ClearColumn(const COORD & cleanCoord)
Purpose: This function runs after column check has returned true.  It is passed
a coordinate of the lowest row index corresponding to that column.

Precondition:  THis function runs after the user has successfully placed a piece onto the
board.

Postcondition:  This function determines whether to clear a column or not. If it returns true, it will clear
open up space for the user on the board. If false, it will do nothing*/
void GameBoard::ClearColumn(const COORD & cleanCoord)
{
	
	char ClearSym = 176;
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	

	for (short i = 0; i < 9; i++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (1+2*cleanCoord.X), i  });
		cout << ClearSym;
		
		mGameGrid[cleanCoord.X][i].symbolType = ClearSym;
		mGameGrid[cleanCoord.X][i].color = 0;
		
	}
}


/*void GameBoard::Output(COORD startCoord, COORD finishCoord, Symbol symbol)
Purpose: This function places a piece onto the grid

Precondition: This function is only called after symbol check has returned true because it 
modifies the outward appearance of the board.  

Postcondition:  This function will modify the board appearance*/
void GameBoard::Output(COORD startCoord, COORD finishCoord, Symbol symbol)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { ((startCoord.X)*2), startCoord.Y});

	if (symbol.symbolType == -20)
		symbol.symbolType = 176;

	for (int i = startCoord.Y; i < finishCoord.Y; i++)
	{
		for (int j = startCoord.X; j < finishCoord.X; j++)
		{
			cout << V_LINE;
			if(symbol.color!=BLANK)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (symbol.color|FOREGROUND_INTENSITY));
			cout << symbol.symbolType;
			
			mGameGrid[j][i] = symbol;
		}
		cout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//restore to white
}


/*COORD & GameBoard::SetSymbol(int & difficulty)
Purpose: This function calls for a new random piece and then waits for the user to specify a coordinate to place it.
It then calls symbolCheck which will verify whether or not the symbol can be placed onto the board.

Precondition: This function is called over and over again from the main menu until the user has either
filled the caldron or filled every square on the board.

Postcondition:  This function will call outputSymbol after it has verified that the current piece can be placed.
Because of this, it modifies the output to the console.*/
COORD & GameBoard::SetSymbol(int & difficulty)
{
	Symbol newSym = GetNewSymbol(difficulty);
	Symbol temp;
	DWORD x = 0;
	COORD promptCoord = { 0, 0 };
	bool symbolPass = false;
	bool potFill = false;
	char answer, answer2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);		//WHITE
	
	
	while (!symbolPass)
	{
		promptCoord = { 0,0 };

		FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0, 550, { 0, 10 }, &x);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 10 });

		cout << "\nSymbol(";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (newSym.color | FOREGROUND_INTENSITY));

		cout << newSym.symbolType;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << ") to set\n\nPress 'X' to put it in the Calderon";

		if (newSym.symbolType == -20)
		{
			cout << "\nREMOVE A SYMBOL";
		}

		promptCoord = KeyboardHandling().KeyHandler(promptCoord);

		if (promptCoord.Y == 10)
		{
			potFill=DumpPot(newSym);
			if (potFill)
				promptCoord = { 11, 10 };
			else
				promptCoord = { 10, 10 };		
			
			symbolPass = true;
		}

		else
		{
			potFill = SymbolCheck(newSym, promptCoord);

			if (potFill)
			{
				temp.symbolType = FULL_POT;
				DumpPot(temp);
				symbolPass = true;
			}
			else
			{
				promptCoord = { 10, 10 };
				
			}
		}
	}
	if (promptCoord.Y != 10)
	{
		Output(promptCoord, { promptCoord.X + 1, promptCoord.Y + 1 }, newSym);

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 26, 8 });
		
		cout << "{ " << mScore << " }";
	}
	return promptCoord;
}


/*bool GameBoard::DumpPot(Symbol dumpSym)
Purpose: This function controlls the flow of the discarded pieces.  It checks if the user can
discard any more pieces acts accordingly.

Precondition: This function is only called when the user discards a piece "pressing x key".

Postcondition:  This function will either fill the pot up by one or
terminate the game.*/
bool GameBoard::DumpPot(const Symbol &dumpSym)
{
	short i = 0;
	short temp = 0;
	bool fullPot = false;
	DWORD x;

	if (dumpSym.symbolType == FULL_POT)
	{
		
		for (i = 0; i < CAULDRON_BOUNDARY; i++)
		{
			if (mPot[0][i+1].symbolType == 0)
			{
				mPot[0][i].symbolType = 0;
				FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0, 1, { (26+(2*i)) , 4 }, &x);
			}
		}

	}
	else if (dumpSym.symbolType == EMPTY_POT)
	{
		for (i = 0; i < CAULDRON_BOUNDARY; i++)
			mPot[0][i].symbolType = 0;
	}
	else {
		for (i = 0; i < CAULDRON_BOUNDARY; i++)
		{
			if (mPot[0][i].symbolType == 0)
			{
				mPot[0][i] = dumpSym;

				if (i == 3)
				{
					fullPot = true;
				}
				temp = i;
				i = 3;
			}
		}

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (26 + (temp * 2)), 4 });
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (dumpSym.color | FOREGROUND_INTENSITY));


		cout << dumpSym.symbolType;
	}
	return fullPot;

	
}


/*Symbol & GameBoard::GetNewSymbol(int difMod)
Purpose: This function generates a unique symbol for the user to get.
It does this by calling the rand function when determining attributes.

Precondition: This function is called when a new piece is ready to be 
put on the board.  

Postcondition:  This function will return a unique symbol for the user.  
It will then be displayed to the console window*/
Symbol & GameBoard::GetNewSymbol(int difMod)
{
	int selector= rand()% (50);
	Symbol returnSym;
	
	if (selector == 0)				//WILD CARD
	{
		returnSym.symbolType = (char)35;
		returnSym.color = 0;
	}

	else if (selector == 1)		//BOMB
	{
		returnSym.symbolType = (char)236;
		returnSym.color = 0;
	}
	else
	{
		
		returnSym.color = rand() % (5 + difMod)+1;


		int temp = (rand() % (5 + difMod)) + 228;
		returnSym.symbolType = (char)temp;

		temp = returnSym.symbolType;
	}
	return returnSym;
}

/*bool GameBoard::SymbolCheck(Symbol & passed, COORD checkCord)
Purpose: This function performs a  logic check for the symbol.  
Since symbols can't be placed just anywhere, a certain amount of checks
must be performed.  These include checking if the surrounding spaces
are either white space, symbol occupied, or edges.

Precondition: This function is called whenever a user tries to place a symbol
on the board.  

Postcondition:  This function returns a bool that confirms whether or not
a user can place a symbol*/
bool GameBoard::SymbolCheck(Symbol & passed, COORD checkCord)
{
	int whiteSpaceCount = 4;	
	int tempScore = 4;
	short binaryPass = 0;

	int tempSym = 0;
	int tempColor = 0;

	if (passed.symbolType != -20)
	{
		if ((mGameGrid[checkCord.X][checkCord.Y].symbolType != -2) && (mGameGrid[checkCord.X][checkCord.Y].symbolType != -80))		//if square is not empty
			return false;
	}
	

	if ((passed.symbolType != 35) && (passed.symbolType != -20))
	{
		binaryPass = BinaryTag(checkCord, whiteSpaceCount);



		if ((binaryPass & 0b0001) != 0)	// x!=0;
		{
			tempSym = mGameGrid[(checkCord.X - 1)][checkCord.Y].symbolType;
			tempColor = mGameGrid[(checkCord.X - 1)][checkCord.Y].color;

			if ((tempSym != passed.symbolType) && (tempColor != passed.color))
			{
				if ((tempSym != -2) && (tempSym != 35) && (tempSym != -80))			//space is occupied by missmatching symbol
				{
					return false;
				}
				if ((tempSym == -2) || (tempSym == -80))		//space is occupied by white space.  IF 4 whitespaces; then no deal
				{
					whiteSpaceCount++;
				}
			}
		}

		if ((binaryPass & 0b0010) != 0) // x!=8
		{
			tempSym = mGameGrid[(checkCord.X + 1)][checkCord.Y].symbolType;
			tempColor = mGameGrid[(checkCord.X + 1)][checkCord.Y].color;

			if ((tempSym != passed.symbolType) && (tempColor != passed.color))
			{
				if ((tempSym != -2) && (tempSym != 35) && (tempSym != -80))		//space is occupied by missmatching symbol
				{
					return false;
				}
				if ((tempSym == -2) || (tempSym == -80))
				{
					whiteSpaceCount++;
				}
			}
		}

		if ((binaryPass & 0b0100) != 0) //y!= 0
		{
			tempSym = mGameGrid[checkCord.X][(checkCord.Y - 1)].symbolType;
			tempColor = mGameGrid[checkCord.X][(checkCord.Y - 1)].color;

			if ((tempSym != passed.symbolType) && (tempColor != passed.color))
			{
				if ((tempSym != -2) && (tempSym != 35) && (tempSym != -80))
				{
					return false;
				}
				if ((tempSym == -2) || (tempSym == -80))
				{
					whiteSpaceCount++;
				}

			}
		}

		if ((binaryPass & 0b1000) != 0) //y != 8
		{
			tempSym = mGameGrid[checkCord.X][(checkCord.Y + 1)].symbolType;
			tempColor = mGameGrid[checkCord.X][(checkCord.Y + 1)].color;

			if ((tempSym != passed.symbolType) && (tempColor != passed.color))
			{
				if ((tempSym != -2) && (tempSym != 35) && (tempSym != -80))
				{
					return false;
				}
				if ((tempSym == -2) || (tempSym == -80))
				{
					whiteSpaceCount++;
				}
			}
		}


		tempScore -= whiteSpaceCount;
		tempScore *= 5;
		mScore += tempScore;

		if (whiteSpaceCount < 4)
			return true;

		return false;
	}
	else return true;
}


/*short GameBoard::BinaryTag(const COORD & checkCoord, int & wsOffset)
Purpose: This function analyzes the current coordinate that user is trying
to place a symbol at and assigns a tag to the symbol.  The tag identifies 
if the symbol is placed on an column edge, a row edge, both, or neither. 
The symbol check function then uses this tag to identify what conditional
checks it can perform on the desired piece.

Precondition: This function is called from Symbol check, therefore the user 
must be placing a piece for it to be called.

Postcondition:  The returned value is a bit series that will be used 
and masked by Symbol check*/
short GameBoard::BinaryTag(const COORD & checkCoord, int & wsOffset)
{
	short binarPass = 0;


	if (checkCoord.X != 0)
	{
		wsOffset--;
		binarPass = (binarPass | 1);// 0b0001);
	}

	if (checkCoord.X != 8)
	{
		wsOffset--;
		binarPass = (binarPass | 2);// 0b0010);
	}

	if (checkCoord.Y != 0)
	{
		wsOffset--;
		binarPass = (binarPass | 4);// 0b0100);
	}

	if (checkCoord.Y != 8)
	{
		wsOffset--;
		binarPass = (binarPass | 8);//0b1000);
	}


	return binarPass;
}


/*int GameBoard::CheckLeaderBoard()
Purpose: This function analyzes the current leaders stored in the leaderfile
 and decides whether the user is able to submit their record.

Precondition: The user must finish a game before they can be considered 
for a leader spot.

Postcondition:  The returned value is a bool that confirms or denies 
the users eligibility for the record board.*/
int GameBoard::CheckLeaderBoard()
{
	char cScore[40] = { 0 };
	int value=0;
	int cArrayDex= 0;
	int indexPointer = 0;

	std::string::const_iterator it;

	for (indexPointer = 0; indexPointer < 4; indexPointer++)
	{
		it = mFileContents[indexPointer].begin();

		while (it != mFileContents[indexPointer].end())
		{
			if(std::isdigit(*it))
			{

				cScore[cArrayDex] = *it;
				//value= atoi(&cScore[someIndex]);
				cArrayDex++;
			}
			it++;
		}
		if (atoi(cScore) < mScore)	//mul mScore by 5
		{
			return indexPointer;
		}

		for (int i = 0; i < 40; i++)
			cScore[i] = '\0';
		cArrayDex = 0;
	}

	return indexPointer;
}

/*void GameBoard::EnterName(int scoreIndex)
Purpose: This function lets the user enter their name to be stored in the 
 leader board. 

Precondition: The user must finish a game with a score over one of the top 
 for leaders.

Postcondition:  The users name is written to a text file which is saved
 for later reference.*/
void GameBoard::EnterName(int scoreIndex)
{
	string newName;
	char score[5] = { 0 };

	string temp[4];
	

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	do {
		system("cls");
		cout << "Please Enter your name: ";
		getline(cin, newName);
	} while (newName.length() > 40);

	int i = 0;
	while (i <scoreIndex)
	{

		if (!mFileContents[i].empty())
		{
			temp[i] = mFileContents[i];
		}
		i++;
	}



	newName= newName+ " " + itoa((mScore), score, 10);

	//set score at back;
	temp[scoreIndex] = newName;


	while (i < 3)
	{

		if (!mFileContents[i].empty())
		{
			temp[i+1] = mFileContents[i];
		}
		i++;
	}


	mFileContents = temp;
	mGameFile.WriteToFile(mFileContents);

	

}

