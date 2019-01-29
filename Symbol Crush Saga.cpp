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

const int SIZE = 9; //declare constant for the size of the array
enum Symbols {EXCLAMATION_POINT = 33, DOUBLE_QUOTES, HASHTAG, DOLLAR_SIGN, PERCENTAGE, AMPERSAND}; //Declare enumeration for the array
typedef Symbols* SymbolsPtr; // Create a type for the enum pointer.
struct Data // Declare struct
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
	Data GameData; // Declare variable GameData of the struct type Data

	GameData.moves = 0; //Initialize number of moves
	GameData.score = 0; //Initialize score

	SymbolsPtr *board = new SymbolsPtr[SIZE]; //Declare a pointer of the IntPntr type.

	for(int i = 0; i < SIZE; i++) //Initialize dynamic array for the gameboard
	{
		board[i] = new Symbols[SIZE];
	}
	
	printinfo(); // Call the print info function

	initialize_board(board); // Call function to initialize board

	cout << "Initializing board..." << endl << endl;

	for (int i = 0; i < 10; i++) //Sets number of moves to 10 and begins the game
	{	
		print_board(board); // call print_board function to print the gameboard

		cout << "   Moves:  " << GameData.moves << " Score:  " << GameData.score << endl; // Displays moves and score

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
	//Prints my information.
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
	srand(time(NULL)); // Seed the RNG	
	int i, j; // Declare 2 variables, i for vertical size of array, j for horizontal size.

	for(i = 0; i < SIZE; i++)// Controls first variable in array
	{
		for(j = 0; j < SIZE; j++) // Controls second variable in array
		{	
			// Generate a random number between 33 and 38, typecasted as enumeration type of Symbol, then store into the array
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
	int i, j; // Declare 2 variables, i for vertical size of array, j for horizontal size.
	char letter;// Declare char letter

	// Print out the board

	cout << "    1 2 3 4 5 6 7 8 9\n"
	     << "  +-------------------+\n";

	for(i = 0; i < SIZE; i++)
	{
		letter = 'A' + i; // Increase value of each letter for each iteration of the vertical for loop
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
	char d = 0, dir = 0; // d is the function placeholder for GameData.ROW before it is converted into an int, dir is the function placeholder for GameData.direction
	int i, j, k, n, f = 0, max; // i and j are the function indexes, k holds the constant value of the given array position, n is the counter, f is the function placeholder for GameData.score, max stores the lowest point a vertical match reaches

	coord_check(GameData); // Call the coord_check function
	
	if(GameData.ROW == 'R' && GameData.COL == 0) // If user entered R0
	{		
		initialize_board(board); // Reshuffle board
		return; // Break out of the move() function
	}
		
	do
	{	//Prompt user to input a direction to check on the gameboard
		cout << "Enter Direction (V = Vertical, H = Horizontal): ";
		cin >> 	GameData.direction; 
		
		dir = GameData.direction; // Sets dir equal to the struct directional value to make code cleaner
		
		if((dir != 'V') && (dir != 'v') && (dir != 'H') && (dir != 'h')) // Checks to make sure input is valid
		{
			cout << "Invalid entry. Try again... " << endl;
		}

	}while((dir != 'V') && (dir != 'v') && (dir != 'H') && (dir != 'h'));

	j = GameData.COL; //Sets j equal to the struct column value to make code cleaner

	i = static_cast<int>(GameData.ROW)-65; //Convert the user entered char into an int value and subtract ASCII value so it can be used as an index
	j = j - 1; //Subtract one from the user entered integer value to be used as an array.

	k = board[i][j]; // Set k, constant, to the value of the array at initial user inputted index

	if((dir == 'H') || (dir == 'h')) // If user enters H or h for horizontal
	{
		n = 0; // Set counter to 0

		while(board[i][j+n] == k) // Check to see if array value with j + n is equal to the initial user inputted array value
		{
			f = f + 1; // Add one to the f, which represents score
			n++; // Increment counter
		}

		n = 1; // Set counter to 1 to check in other direction
		while(board[i][j-n] == k)// Check to see if array value with j-+ n is equal to the initial user inputted array value

		{
			f = f + 1; // Add one to f, which represents score
			n++; // Increment counter
		}
	}
	else // If user enters v or V for vertical
	{	
		n = 0; // Set counter to 0

		if(i !=	8) // If entered value is not on the bottom row of the board
		{ 	
			while((board[i+n][j] == k))// Check to see if array value with i + n is equal to the initial user inputted array value
			{
				f = f + 1; // Add one to score
				n++; // Increment counter
				
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
				f = f + 1; // Add one to score
				n++; // Increment counter

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
		GameData.score = GameData.score + f; // Add one to the struct total score
		
		cout << "Good job! You gained +" << f << " points!" << endl;
	
// EXTRA CREDIT SPOT: THE VALUES ARE SHIFTED DOWN THE COLUMNS INSTEAD OF RANDOMLY IN THE SPOT THE MATCH WAS MADE

		if((dir == 'H') || (dir == 'h')) // For if the user chose to match a horizontal direction
		{
			n = 0; // Set counter to 0

			while(board[i][j+n] == k) // Check to see if array value with j + n is equal to the initial user inputted array value
			{
				while(i > 0)
				{
					board[i][j+n] = board[i-1][j+n]; // Sets each array equal to the one above it and continue this trend to the top of the board
					i--; // Decrements i
				}
				board[0][j+n] = static_cast<Symbols>(rand() % 6 + 33); // Create a new random symbol at the top of the board
				
				i = static_cast<int>(GameData.ROW)-65; //Resets i value
				
				n++; // Increment counter
			}

			i = static_cast<int>(GameData.ROW)-65; //Resets i value
			
			n = 1; // Set counter to 1
			while(board[i][j-n] == k)// Check to see if array value with j - n is equal to the initial user inputted array value
			{
				while(i > 0)
				{
					board[i][j-n] = board[i-1][j-n]; // Sets each array equal to the one above it and continue this trend to the top of the board
					i--; // Decrements i
				}
				board[0][j-n] = static_cast<Symbols>(rand() % 6 + 33); // Create a new random symbol in place of one of the matched ones
				
				i = static_cast<int>(GameData.ROW)-65; //Resets i value

				n++; // Increment counter
			}
		}
		else
		{	
			n = 0; // Set counter to 0
			if(i !=	8) // If the inputted value is on the bottom of the board
			{
				while((board[i+n][j] == k))// Check to see if array value with i + n is equal to the initial user inputted array value
				{
					if(i+n-f < 0) // If a value to be "dropped down" is off the board, randomize the position instead
					{
						board[i+n][j] = static_cast<Symbols>(rand() % 6 + 33);
					}
					else // The vslue of the given array is set to the value of the one "f" spaces above it
					{
						board[i+n][j] = board[i+n-f][j];
						board[i+n-f][j] = static_cast<Symbols>(rand() % 6 + 33);// Then randomized
					}					
					n++;// Increment counter
					
					if(i+n > 8) // break loop if index would exceed max array value
					{
						break;
					}
				}
			}

			n = 1; // Set counter to 1
			if(i != 0) // If the inputted value is not at the top of the board
			{
				if(i == 8) // If the inputted value is at the bottom of the board
				{
					n = 0; // Set counter to 0 instead
				}

				while(n < (max-f)) //Continue looping while the counter is less than the lowest space achieved by the given match subtracted by the length of the match
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
					n++; // Increment counter

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

	return;	// End function
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
	
	int flag = 0; // Declares a flag to check the conditions of the loop
	string coordinates; // Declares a string for the user to enter their coordinates

	do
	{	
		cout << "Enter location for move #" << GameData.moves + 1 << " (e.g, B7): ";
		
		cin >> coordinates; // Input coords

		GameData.ROW = coordinates[0]; // The row value
		GameData.COL = coordinates[1] - 48; // The column value, adjusted for conversion

		if(islower(GameData.ROW)) // If a letter is lowercase, convert it to uppercase
		{
			GameData.ROW = toupper(GameData.ROW);
		}

		if(GameData.ROW == 'R' && GameData.COL == 0) // If user enters R0, reshuffle the board
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
		else if((GameData.ROW < 'A') || (GameData.ROW > 'I') || (GameData.COL < 1) || (GameData.COL > 9)) // If the coordinates are not within these ranges have them enter a new coordinate
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
