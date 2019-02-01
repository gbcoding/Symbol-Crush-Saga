/*
+=========================================================================+
| Program Name: Symbol Crush Saga.cpp                                          |
| Author: Garrett Brumley (grb0065)                                       |
| Class: CSCE 1030 Section 001                                            |
| Date: 4/22/2016                                                         |
| Description: Symbol Crush Saga|
+=========================================================================+
*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cctype>
#include <string>
using namespace std;

const int SIZE = 9; // constant for the size of the array
enum Symbols {EXCLAMATION_POINT = 33, DOUBLE_QUOTES, HASHTAG, DOLLAR_SIGN, PERCENTAGE, AMPERSAND}; 
typedef Symbols* SymbolsPtr; 

// Holds data for the game
struct Data 
{	
	int moves;
	int score;
	char ROW;
	int COL;
	char direction;

};

// Function declarations 
void printinfo();
void initialize_board(SymbolsPtr *board);
void print_board(SymbolsPtr *board);
void coord_check(Data& GameData);
void move(SymbolsPtr *board, Data& GameData);

int main()
{
	Data GameData; 
	GameData.moves = 0; 
	GameData.score = 0; 
	SymbolsPtr *board = new SymbolsPtr[SIZE]; .

	//Initialize dynamic array for the gameboard
	for(int i = 0; i < SIZE; i++) 
	{
		board[i] = new Symbols[SIZE];
	}
	
	printinfo(); 
	initialize_board(board); 

	cout << "Initializing board..." << endl << endl;

	//Set 10 moves for game length and plays game
	for (int i = 0; i < 10; i++) 
	{	
		print_board(board); 

		cout << "   Moves:  " << GameData.moves << " Score:  " << GameData.score << endl; 

		move(board, GameData); // Function that parses user inputted moves
				
		GameData.moves = GameData.moves + 1; // Add 1 to the move counter
	}

	cout <<	"-----------------------------------------------------------\n"
	     <<	"*                W E L L   P L A Y E D!                   * \n"
	     <<	"*                                                         * \n"
	     <<	"*                 Your final score was:                   * \n"
	     <<	"*                                                         * \n"
	     <<	"*                          " << GameData.score << "                             * \n"
	     <<	"*                                                         * \n"
	     <<	"-----------------------------------------------------------\n" << endl;
		

	for(int i = 0; i < SIZE; i++) //Delete the dynamic array
	{
		delete [] board[i];
	}
	delete [] board;

	return 0; // End program
}

/*
=========================================================================================
Function: printinfo
Parameters: None
Return: Printed text
Description: This function prints my class info and game info
=========================================================================================
*/
void printinfo()
{
	cout << "    +------------------------------------------------+\n"
	     << "    |       Computer Science and Engineering         |\n"
	     << "    |        CSCE 1030 - Computer Science I          |\n"
	     << "    | Garrett Brumley  grb0065  gbrum2014@gmail.com  |\n"
	     << "    +------------------------------------------------+\n" << endl;

	cout <<	"-----------------------------------------------------------\n"
	     <<	"        W e l c o m e   t o   1 0 3 0   C r u s h          \n"
	     <<	endl
	     <<	"This program will randomly initialize your game board using\n"
	     <<	"a set of 6 characters (!, \", #, $, %, &) that a player will\n"
	     <<	"then attempt to match a combination of 3 or more characters\n"
	     <<	"to gain points in a finite set of moves or time duration.\n"
	     << endl
	     << "You will enter the coordinates of the spot on the board\n"
	     << "where you see a match, then enter the direction of the match\n"
	     << endl
	     << "Should you find you've run out of matches, entering R0 will\n"
	     << "reshuffle the board. Good luck!\n"  
	     <<	"-----------------------------------------------------------\n" << endl;

	return;
}

/*
=========================================================================================
Function: initialize_board
Parameters: Array of type Symbol
Return: A processed array with stored symbol values in it.
Description: This function takes in an Array, then processes it by randomly storing
	a number between 33 and 38 in each pair of indecies
=========================================================================================
*/
void initialize_board(SymbolsPtr *board)
{
	// Seed RNG, i for vertical array, j for horizontal array
	srand(time(NULL)); 	
	int i, j; 
	
	// Generate a random number between 33 and 38, typecasted as enumeration type of Symbol, then store into the array
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++) 
		{		
			board[i][j] = static_cast<Symbols>(rand() % 6 + 33); 
		}	
	}
	return;
}
/*
=========================================================================================
Function: print_board
Parameters: Array of type Symbol
Return: The game board using the array
Description: This function prints out the game board using a combination of cout strings
	and the processed array.
=========================================================================================
*/
void print_board(SymbolsPtr *board)
{
	int i, j; 
	char letter;

	cout << "    1 2 3 4 5 6 7 8 9\n"
	     << "  +-------------------+\n";

	for(i = 0; i < SIZE; i++)
	{
		letter = 'A' + i; 
		cout << letter << setw(2) << "|"; // Left border
		for(j = 0; j < SIZE; j++)
		{
			cout << setw(2) << static_cast<char>(board[i][j]); // Typecast the array into the char type and print to board
		}
		cout << setw(2) << "|" << endl;	// Right border
	}
	cout << "  +-------------------+\n";
	return;
}
/*
=========================================================================================
Function: move
Parameters: Dynamic Array, Call-by-reference Struct
Return: A completed move sequence
Description: This function calculates the effects of user input on the gameboard utilizing
	the dynamic 2D array.
=========================================================================================
*/
void move(SymbolsPtr *board, Data& GameData)
{
	// d holds GameData.ROW, dir holds GameData.direction
	char d = 0, dir = 0; 
	// i and j are indexes, k holds the constant value of the given array position, 
	// n is the counter, f holds local move score, max stores the lowest point a vertical match reaches
	int i, j, k, n, f = 0, max; 

	coord_check(GameData); 

	// If user entered R0, reshuffle board
	if(GameData.ROW == 'R' && GameData.COL == 0) 
	{		
		initialize_board(board); 
		return;
	}
	
	// Prompt for direction to check
	do
	{	
		cout << "Enter Direction (V = Vertical, H = Horizontal): ";
		cin >> 	GameData.direction; 	
		dir = GameData.direction; 
		
		// Input checking
		if((dir != 'V') && (dir != 'v') && (dir != 'H') && (dir != 'h')) 
		{
			cout << "Invalid entry. Try again... " << endl;
		}

	}while((dir != 'V') && (dir != 'v') && (dir != 'H') && (dir != 'h'));

	j = GameData.COL; 

	//Convert the user entered char and column into index values
	i = static_cast<int>(GameData.ROW)-65; 
	j = j - 1; 
	
	// Set k, constant, to the value of the array at initial user inputted index
	k = board[i][j]; 

	// If user enters H or h for horizontal
	if((dir == 'H') || (dir == 'h')) 
	{
		n = 0; 
		// Check to see if array value with j + n is equal to the user inputted array value
		while(board[i][j+n] == k) 
		{	
			// Add one to the score, then increment
			f = f + 1; 
			n++; 
		}

		n = 1; // Set counter to 1 to check in other direction
		while(board[i][j-n] == k)// Check to see if array value with j - n is equal to the initial user inputted array value

		{
			f = f + 1; // Add one to f, which represents score
			n++; // Increment counter
		}
	}
	else // If user enters v or V for vertical
	{	
		n = 0; 	
		// If entered value is not on the bottom row of the board
		if(i !=	8) 
		{ 	
			// Check to see if array value with i + n is equal to the initial user inputted array value
			while((board[i+n][j] == k))
			{
				// Add one to score, Increment counter
				f = f + 1; 
				n++; 
				
				if(i+n > 8) // If loop approaches bottom border, break out of loop to avoid segmentation fault
				{
					break;
				}
			}
			max = i+n; // Set max value to i+n at the end of the loop for calculation of vertical value dropdown
		}

		n = 1; // Set counter to 1 to check in other direction
		
		if(i != 0)
		{
			if(i == 8) // If entered value is at the bottom of the board, set counter to 0 and only check upwards
			{
				n = 0;
			}

			while((board[i-n][j] == k)) // Check to see if array value with i - n is equal to the initial user inputted array value
			{	
				f = f + 1; // Add one to score, Increment counter
				n++; 

				if(i-n < 0) // If loop approaches top border, break out of loop to avoid segmentation fault
				{
					break;
				}
			}
		}
	}

	//Check to see if 3 of a kind has been matched
	if(f >= 3)
	{	
		GameData.score = GameData.score + f; // Add points to the global score
		
		cout << "Good job! You gained +" << f << " points!" << endl;
	
		// EXTRA CREDIT SPOT: THE VALUES ARE SHIFTED DOWN THE COLUMNS INSTEAD OF RANDOMLY IN THE SPOT THE MATCH WAS MADE

		if((dir == 'H') || (dir == 'h')) // For if the user chose to match a horizontal direction
		{
			n = 0; 

			while(board[i][j+n] == k) // Check to see if array value with j + n is equal to the initial user inputted array value
			{
				// Sets each array equal to the one above it and continue this trend to the top of the board
				while(i > 0)
				{
					board[i][j+n] = board[i-1][j+n]; 
					i--; 
				}
			
				// Create a new random symbol at the top of the board
				board[0][j+n] = static_cast<Symbols>(rand() % 6 + 33); 
				i = static_cast<int>(GameData.ROW)-65; 
				n++; 
			}

			i = static_cast<int>(GameData.ROW)-65; //Resets i value
			
			n = 1; // Set counter to 1
			
			// Check to see if array value with j - n is equal to the initial user inputted array value
			while(board[i][j-n] == k)
			{
				// Sets each array equal to the one above it and continue this trend to the top of the board
				while(i > 0)
				{
					board[i][j-n] = board[i-1][j-n]; 
					i--; 
				}
			
				// Create a new random symbol in place of one of the matched ones
				board[0][j-n] = static_cast<Symbols>(rand() % 6 + 33); 
				i = static_cast<int>(GameData.ROW)-65; 
				n++; 
			}
		}
		else
		{	
			n = 0; 
			// If the inputted value is on the bottom of the board
			if(i !=	8) 
			{
				// Check to see if array value with i + n is equal to the initial user inputted array value
				while((board[i+n][j] == k))
				{
					// If a value to be "dropped down" is off the board, randomize the position instead
					if(i+n-f < 0) 
					{
						board[i+n][j] = static_cast<Symbols>(rand() % 6 + 33);
					}
					else // The value of the given array is set to the value of the one "f" spaces above it, then randomized
					{
						board[i+n][j] = board[i+n-f][j];
						board[i+n-f][j] = static_cast<Symbols>(rand() % 6 + 33);
					}					
					n++;
			
					// break loop if index would exceed max array value
					if(i+n > 8) 
					{
						break;
					}
				}
			}

			n = 1;
			
			// If the inputted value is not at the top of the board
			if(i != 0) 
			{
				// If the inputted value is at the bottom of the board, set counter to 0 instead
				if(i == 8) 
				{
					n = 0; 
				}

				//Continue looping while the counter is less than the lowest space achieved by the given match subtracted by the length of the match
				while(n < (max-f)) 
				{	
					if(i-n-f < 0)
					{
						board[i-n][j] = static_cast<Symbols>(rand() % 6 + 33);
					}
					else // The value of the given array is set to the value of the one "f" spaces above it
					{
						board[i-n][j] = board[i-n-f][j];
						board[i-n-f][j] = static_cast<Symbols>(rand() % 6 + 33); // Then randomize
					}
					n++; 

					if(i-n < 0) // If loop approaches top border, break out of loop to avoid segmentation fault
					{
						break;
					}
				}
			}
		}		
	}
	else // Loop if user did not enter V, v, H, or h
	{
		cout << "You did not pick a 3 of a kind" << endl;
	}

	return;	
}

/*
=========================================================================================
Function: coord_check
Parameters: Call-by-reference Struct 
Return: A validated set of coordinates ready for the move function
Description: This function prompts a user to input a string of 2 coordinates which are 
	then checked to make sure they're in the bounds of the array.
=========================================================================================
*/
void coord_check(Data& GameData)
{
	
	int flag = 0; // Flag to check the conditions of the loop
	string coordinates; 

	do
	{	
		cout << "Enter location for move #" << GameData.moves + 1 << " (e.g, B7): ";
		cin >> coordinates; 

		GameData.ROW = coordinates[0]; // The row value
		GameData.COL = coordinates[1] - 48; // The column value, adjusted for conversion

		// If a letter is lowercase, convert it to uppercase
		if(islower(GameData.ROW)) 
		{
			GameData.ROW = toupper(GameData.ROW);
		}

		// If user enters R0, reshuffle the board
		if(GameData.ROW == 'R' && GameData.COL == 0) 
		{
			if(GameData.moves < 9)
			{
				cout << "Reshuffling board... " << endl;
				return;
			}
			else
			{
				return;
			}
		}
		// If the coordinates are not within these ranges have them enter a new coordinate
		else if((GameData.ROW < 'A') || (GameData.ROW > 'I') || (GameData.COL < 1) || (GameData.COL > 9)) 
		{
			flag = 1;
			cout << "You did not enter a valid coordinate. Please try again." << endl;
		}
		else // If coordinates passes the above conditions, continue with the program
		{
			return;
		}
	}while(flag == 1); // Repeats function until broken by a return
}
