#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

//these are my function prototypes
void intro();
void gameboard(char arr[][10], char arr2[][10], char enarr[][10], int& q);
void direction(int& l, int& m, int q, char arr[][10], char arr2[][10]);
void placeship(int& l, int& m, int& q, char arr[][10], int& y, int& u, char enarr2[][10], char arr2[][10]);
int shipsize(int q);
void menuint(char& menu, char arr[][10], char arr2[][10], char enarr[][10], int q, int& y, int& u, char enarr2[][10], int& hit, bool& surrender, int& l, int& m);
void targeting(int& y, int& u, char enarr2[][10], char enarr[][10], int& hit);
void etargeting(int& l, int& m, char arr[][10], int& ehit);
void edirection(int& y, int& u, int q, char enarr2[][10]);
void coord(int& l, int& m, int& q, char arr[][10], char arr2[][10]);
void ecoord(int& y, int& u, int& q, char enarr2[][10]);
void directioncheck(int& l, int& m, int q, int& b, char arr[][10], char& direct, bool& dire);
void edirectcheck(char& direct, int q, int y, int u, char enarr2[][10], int v, bool edire);
void shipname(int q);
void clear();
void endgame(char& play, bool& playagain, bool surrender, int hit, int ehit, int& win, int& lose, int& surrend);

//Pre condition: All of the prototypes must connect to the function properly
//Post condition: The game should be exicuted how it should, properly, minus the sinking ship display
int main()
{
	srand((unsigned)time(NULL));
	//boolean identifier that allows the player to play again
	bool playagain;
	//the character identifier that the user inputs for in order to quit the game or play again
	char play;
	//the coordinate identifiers for the player grid
	int l;
	int m;
	//the coordinate identifiers for the enemy's grid
	int y;
	int u;
	//the identifier for the number of ship placement that the user is on
	int q = 1;
	//the number of wins of the player
	int win = 0;
	//the number of loses of the player
	int lose = 0;
	//the number of times that the player has surrendered
	int surrend = 0;
	//this is a function call to the game's introduction
	intro();
	//the do while loop that allows the player to play as many times as they want
	do
	{
		//the identifier used if the player surrenders
		bool surrender = false;
		//the playagain identifier is set to false so the game can be played again and again
		playagain = false;
		//the player's arrays
		char arr[10][10];
		char arr2[10][10];
		//the computer's arrays
		char enarr[10][10];
		char enarr2[10][10];
		//the number of hits that the player has hit the enemy
		int hit = 0;
		//the number of hits that the player has sustained
		int ehit = 0;
		//the do while loop that keeps the game going until there is a winner or until the player surrenders
		do
		{
			//the identifier used for the player to choose a menu option
			char menu;
			//while loop only goes while q doesn't = 6
			while (q != 6)
			{
				//the gameboard function is called and displayed
				gameboard(arr, arr2, enarr, q);
				//some side info for the user if they don't remember the directions
				cout << "To set your ship use the keys 'w'(up), 's'(down), 'a'(left), 'd'(right)." << endl;
				//the placeship function is called
				placeship(l, m, q, arr, y, u, enarr2, arr2);
				//the clear function call
				clear();
			}
			//the call to the menuint function
			menuint(menu, arr, arr2, enarr, q, y, u, enarr2, hit, surrender, l, m);
		} while (hit != 17 && ehit != 17 && surrender == false);
		//clears the display without user input
		system("CLS");
		//the endgame function call
		endgame(play, playagain, surrender, hit, ehit, win, lose, surrend);
	} while (playagain == true);
	return 0;
}
//Precondition: the identifiers are declaired
//Postcondition: Should output the display
void intro()
{
	//this is all the introduction and the directions pages
	cout << "\n\n\n\n" << setw(70) << "BATTLESHIP: THE GAME\n\n\n\n";
	cout << setw(73) << "Press the Enter key to continue." << endl;
	cout << "\n\n\n" << setw(60) << "###\n" << setw(61) << "#####\n" << setw(62) << "#######\n" << setw(62) << "#######\n";
	cout << setw(62) << "######\n" << setw(61) << "#####\n" << setw(60) << "###\n" << setw(58) << " ##\n";
	cout << setw(59) << "|--|\n" << setw(61) << "<=={###         <=={###    ____    _____|__|__\n" << setw(45) << "____/__";
	cout << char(92) << "___/_____" << char(92) << "____" << char(92) << "______\n";
	cout << setw(39) << char(92) << " o   o   o   o   o   o   o  |" << endl << setw(80);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	//clears the display
	cin.ignore();
	system("CLS");
	cout << setw(75) << "Directions\n 1. Use the 'w'(up) 's'(down) 'a'(left) and 'd'(right) keys to set your ship position.";
	cout << "\n\n 2. There are a total of five ships.\n\n";
	cout << " 3. The destroyer is two segments long.\n\n 4. The submarine and cruiser are each three segments long.";
	cout << "\n\n 5. The battleship is four segments long.\n\n 6. The carrier is five segments long.\n\n";
	cout << " 7. The game ends when either the player or the computer has sunk all five ships or the player chooses to surrender." << endl;
	//call to the clear function
	clear();
}
//Precondition: the arrays should be declaired and q should be initialized
//POstcondition: the gameboard should display to the screen with the proper characters
void gameboard(char arr[][10], char arr2[][10], char enarr[][10], int& q)
{
	//outputs the top part of the board
	cout << setw(26) << "Your Shipyard" << setw(55) << "Enemy Shipyard" << endl;
	cout << "X | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10|" << setw(55) << "X | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10|" << endl;
	//for loop that initializes 10 columns
	for (int i = 0; i < 10; i++)
	{
		//spacers to make display look nice
		cout << "__|___|___|___|___|___|___|___|___|___|___|" << setw(55) << "__|___|___|___|___|___|___|___|___|___|___|" << endl;
		//if statement that outputs the y-axis numbers -10
		if (i < 9)
		{
			cout << i + 1 << " |";
		}
		//if statement that outputs the 10 on the y-axis
		if (i == 9)
		{
			cout << "10|";
		}
		//for loop that initializes 10 line
		for (int j = 0; j < 10; j++)
		{
			//this if statement intitializes the first and second arrays
			if (q == 1)
			{
				arr2[i][j] = '~';
				arr[i][j] = '~';
			}
			//outputs the characters of the player array
			cout << " " << arr[i][j] << " |";
		}
		//spaces the computer array from the player
		cout << setw(13);
		//if statement outputs the enemy's y-axis
		if (i < 9)
		{
			cout << i + 1 << " |";
		}
		//if statement outputs 10 to the y-axis
		if (i == 9)
		{
			cout << setw(15) << "10|";
		}
		//for loop initializes 10 lines on the enemy side
		for (int k = 0; k < 10; k++)
		{
			//initializes enemy array
			if (enarr[i][k] != 'H' && enarr[i][k] != 'M')
				enarr[i][k] = '~';
			//outputs enemy array
			cout << " " << enarr[i][k] << " |";
		}
		cout << endl;
	}
	//outputs spacing on the bottom of boards to make it look nice
	cout << "__|___|___|___|___|___|___|___|___|___|___|" << setw(55) << "__|___|___|___|___|___|___|___|___|___|___|" << endl;
}
//precondition: thegameboard should be displayed 
//postcondition: the ships for both sides should be initialized
void placeship(int& l, int& m, int& q, char arr[][10], int& y, int& u, char enarr2[][10], char arr2[][10])
{
	//switch statement that allows user to input coordinates and direction of ships
	switch (q)
	{
	case 1:  coord(l, m, q, arr, arr2);
		direction(l, m, q, arr, arr2);
		break;
	case 2:	 coord(l, m, q, arr, arr2);
		direction(l, m, q, arr, arr2);
		break;
	case 3:	 coord(l, m, q, arr, arr2);
		direction(l, m, q, arr, arr2);
		break;
	case 4:  coord(l, m, q, arr, arr2);
		direction(l, m, q, arr, arr2);
		break;
	case 5:	 coord(l, m, q, arr, arr2);
		direction(l, m, q, arr, arr2);
		break;
	}
	//switch statement that inputs information for the enemy's coordinates and direction of their ships
	switch (q)
	{
	case 1:  ecoord(y, u, q, enarr2);
		edirection(y, u, q, enarr2);
		break;
	case 2:	 ecoord(y, u, q, enarr2);
		edirection(y, u, q, enarr2);
		break;
	case 3:	 ecoord(y, u, q, enarr2);
		edirection(y, u, q, enarr2);
		break;
	case 4:  ecoord(y, u, q, enarr2);
		edirection(y, u, q, enarr2);
		break;
	case 5:	 ecoord(y, u, q, enarr2);
		edirection(y, u, q, enarr2);
		break;
	}
	//adds one and assigns to the q identifier
	q++;
}
//precondition: the identifier q should be initialized
//postcondition: the size of the ships being placed are determined
int shipsize(int q)
{
	//switch statement that determines ship size
	switch (q)
	{
	case 1:	 return 2;
		break;
	case 2:	 return 3;
		break;
	case 3:  return 3;
		break;
	case 4:  return 4;
		break;
	case 5:  return 5;
		break;
	}
}
//precondition: the ships of both the user and the enemy should be placed correctly
//postcondition: the menu of the game should be displayed and allow the user to navigate between firing a missile, viewing the game board, or surrendering
void menuint(char& menu, char arr[][10], char arr2[][10], char enarr[][10], int q, int& y, int& u, char enarr2[][10], int& hit, bool& surrender, int& l, int& m)
{
	//outputs the game menu
	cout << "\n\n\n\n\n\n" << setw(70) << "GAME MENU\n\n\n\n" << setw(75) << "The Game Board(Press G)\n\n\n";
	cout << setw(71) << "Fire!(Press F)\n\n\n" << setw(70) << "Surrender(Press S)";
	//user inputted menu choice
	cin >> menu;
	//while statemnet that keeps redisplaying the menu until the user chooses a valid option
	while (menu != 'F' && menu != 'f' && menu != 'G' && menu != 'g' && menu != 'S' && menu != 's')
	{
		cout << "Not a valid input, please try again." << endl;
		clear();
		cout << "\n\n\n\n\n\n" << setw(70) << "GAME MENU\n\n\n\n" << setw(75) << "The Game Board(Press G)\n\n\n";
		cout << setw(71) << "Fire!(Press F)\n\n\n" << setw(70) << "Surrender(Press S)";
		cin >> menu;
	}
	//if g is selected it shows the player the gameboard
	if (menu == 'g' || menu == 'G')
	{
		//clears the screen
		system("CLS");
	}
	//if f is selected then it allows the user to exchange fire with the enemy
	if (menu == 'f' || menu == 'F')
	{
		//call to clear function
		clear();
		//call to target function
		targeting(y, u, enarr2, enarr, hit);
		//call to enemy target function
		etargeting(l, m, arr, hit);
	}
	//if s is selected the current game ends with the user's surrender
	if (menu == 's' || menu == 'S')
	{
		//display that lets the user know that they surrendered 
		cout << "You have failed your country by letting the enemy win!" << endl;
		//sets the boolean identifier surrender to true so that the game may exit into the endgame 
		surrender = true;
	}
	//if statement that displays the gameboard if the user didn't surrender
	if (surrender != true)
	{
		//call to gameboard function
		gameboard(arr, arr2, enarr, q);
		//prompt to clear the display
		cout << endl << setw(70) << "Press the Enter key to continue." << endl;
		cin.ignore();
		cin.ignore();
		//clears display
		system("CLS");
	}
}

//precondition: the coordinate identifiers l and m must be initialized
//postcondition: the ships will be set in the proper direction and displayed on screen
void direction(int& l, int& m, int q, char arr[][10], char arr2[][10])
{
	//creates and sets identifier b to 0
	int b = 0;
	//creates identifier direct for the direction of the ships
	char direct;
	//boolean identifier used for checking validity of chosen direction
	bool dire = false;
	//call to directioncheck function 
	directioncheck(l, m, q, b, arr, direct, dire);
	//while statement that allows the user to pick a coordinate and direction until they are vaild
	while (dire == true)
	{
		//sets identifier dire back to false
		dire = false;
		//sets identifier b to 0
		b = 0;
		// coord function call
		coord(l, m, q, arr, arr2);
		//directioncheck function call
		directioncheck(l, m, q, b, arr, direct, dire);
	}
	//if direct = w then this activates
	if (direct == 'w')
	{
		//adds the previosly subtracted values back on
		l = l + shipsize(q);
		//for loop initializes user array as # and subtracts 1 from indentifier l
		for (int z = 0; z < shipsize(q); z++)
		{
			arr[l][m] = '#';
			l--;
		}
	}
	if (direct == 'd')
	{
		//adds the previosly subtracted values back on
		m = m - shipsize(q);
		//for loop initializes user array as # and adds 1 to indentifier m
		for (int z = 0; z < shipsize(q); z++)
		{
			arr[l][m] = '#';
			m++;
		}
	}
	if (direct == 's')
	{
		//adds the previosly subtracted values back on
		l = l - shipsize(q);
		//for loop initializes user array as # and adds 1 to indentifier l
		for (int z = 0; z < shipsize(q); z++)
		{
			arr[l][m] = '#';
			l++;
		}
	}
	if (direct == 'a')
	{
		//adds the previosly subtracted values back on
		m = m + shipsize(q);
		//for loop initializes user array as # and subtracts 1 from indentifier m
		for (int z = 0; z < shipsize(q); z++)
		{
			arr[l][m] = '#';
			m--;
		}
	}
}

//precontition: the enemy coordinates should be initialized
//postcondition: the enemy's ship direction should be initialized
void edirection(int& y, int& u, int q, char enarr2[][10])
{
	//integer identifier v set = to 0
	int v = 0;
	//boolean identifier = false
	bool edire = false;
	//recreates identifier direct
	char direct;
	//function call edirectcheck
	edirectcheck(direct, q, y, u, enarr2, v, edire);
	//while statement that allows enemy to replace ship until achieves valid direction
	while (edire == true)
	{
		//edire is set to false
		edire = false;
		//v is set to 0
		v = 0;
		//function call ecoord
		ecoord(y, u, q, enarr2);
		//function call edirectcheck
		edirectcheck(direct, q, y, u, enarr2, v, edire);
	}
	//if direct =  w then this activates
	if (direct == 'w')
	{
		//for the size of the ship enemy array is initialized as # and 1 is subtracted from y
		for (int z = 0; z < shipsize(q); z++)
		{
			enarr2[y][u] = '#';
			y--;
		}
	}
	//if direct = d then this activates
	if (direct == 'd')
	{
		//for the size of the ship enemy array is initialized as # and 1 is added to u
		for (int z = 0; z < shipsize(q); z++)
		{
			enarr2[y][u] = '#';
			u++;
		}
	}
	//if direct = s this activates
	if (direct == 's')
	{
		//for the size of the ship enemy array is initialized as # and 1 is added to y
		for (int z = 0; z < shipsize(q); z++)
		{
			enarr2[y][u] = '#';
			y++;
		}
	}
	//if direct = a this activates
	if (direct == 'a')
	{
		//for the size of the ship enemy array is initialized as # and 1 is subtracted from u
		for (int z = 0; z < shipsize(q); z++)
		{
			enarr2[y][u] = '#';
			u--;
		}
	}
}

//precondition: the ships should all be placed on the boards and the user should've selected the fire option at the menu
//postcondition: an H or an M is outputted to the screen depending on if the user hit or missed a ship
void targeting(int& y, int& u, char enarr2[][10], char enarr[][10], int& hit)
{
	//prompt for user to pit x coordinate
	cout << "Select the x coordinate for your missile:";
	//user input x coordinate
	cin >> u;
	//subtracts one from u
	u--;
	//while loop that checks validity of coordinate
	while (u > 9 || u < 0)
	{
		cout << "That coordinate is not on the board.\n";
		cout << "Select the x coordinate for your missile:";
		cin >> u;
		u--;
	}
	//prompt for user to put in y coordinate
	cout << "Select the y coordinate for your missile:";
	//user input y coordinate
	cin >> y;
	//subtracts one from y
	y--;
	//while loop that checks the validity of y
	while (y > 9 || y < 0)
	{
		cout << "That coordinate is not on the board.\n";
		cout << "Select the y coordinate for your missile:";
		cin >> y;
		y--;
	}
	//while loop checks in there is alredy an H or M in that location if so the user mut choose new coordinate
	while (enarr[y][u] == 'H' || enarr[y][u] == 'M')
	{
		cout << "You have already hit there." << endl;
		cout << "Select the x coordinate for your missile:";
		cin >> u;
		u--;
		cout << "Select the y coordinate for your missile:";
		cin >> y;
		y--;
	}
	//output that overviews user's turen
	cout << "Your turn: ";
	cout << "Your missile landed at coordinates (" << u + 1 << "," << y + 1 << "). ";
	//if statement chaecks if user hit a ship
	if (enarr2[y][u] == '#')
	{
		cout << "You have hit an enemy ship!" << endl;
		enarr[y][u] = 'H';
		hit++;
	}
	//else statement is activated in the user didn't hit a ship
	else
	{
		cout << "You missed the shot!" << endl;
		enarr[y][u] = 'M';
	}
}
//precondition: all enemy ships should be placed on the board
//postcondition: the computer should display where they fired their missile and if it was a hit or miss
void etargeting(int& l, int& m, char arr[][10], int& ehit)
{
	//picks random y coordinate btween 1 and 10 and subtracts one
	l = rand() % 10 + 1;
	l--;
	//picks random x coordinate between 1 and 10and subtracts one
	m = rand() % 10 + 1;
	m--;
	//checks to see if the computer has alreay hit that location and repicks coordinates if it did
	while (arr[l][m] == 'H' || arr[l][m] == 'M')
	{
		l = rand() % 10 + 1;
		l--;
		m = rand() % 10 + 1;
		m--;
	}
	//output overviews enemy's turn
	cout << "Enemies turn: ";
	cout << "Enemy's missile landed at coordinates (" << m + 1 << "," << l + 1 << "). ";
	//if statement displays if user ship is hit and initializes H to player aray and adds a hit to enemy total hits
	if (arr[l][m] == '#')
	{
		cout << "One of your ships has just been hit!" << endl;
		arr[l][m] = 'H';
		ehit++;
	}
	//if not a hit than it is a miss and player array initializes M
	else
	{
		cout << "Ha! They missed their shot!" << endl;
		arr[l][m] = 'M';
	}
}

//precondition: the gameboard is initalized
//postcondition: the player coordinates are initalized
void coord(int& l, int& m, int& q, char arr[][10], char arr2[][10])
{
	//prompt for inputting x coordinate
	cout << "Select the x coordinate for your";
	//shipname funct call
	shipname(q);
	//player inputs x coord and subtracts one
	cin >> m;
	m--;
	//checks validity of x coord
	while (m > 9 || m < 0)
	{
		cout << "That is not a valid coordinate, please try again." << endl;
		cout << "Select the x coordinate for your";
		shipname(q);
		cin >> m;
		m--;
	}
	//prompt for y coord input
	cout << "Select the y coordinate for your";
	//funct call for shipname
	shipname(q);
	//user inputs y coord and subtracts one
	cin >> l;
	l--;
	//checks validity of y coord
	while (l > 9 || l < 0)
	{
		cout << "That is not a valid coordinate, please try again." << endl;
		cout << "Select the y coordinate for your";
		shipname(q);
		cin >> l;
		l--;
	}
	//checks validity of both with the use of array 2
	if (arr2[l][m] == '#')
	{
		//allows the player to reinput values if not valid
		while (l > 9 || l < 0 || m > 9 || m < 0 || arr2[l][m] == '#')
		{
			cout << "You cannot place your ship there." << endl;
			cout << "Select the x coordinate for your";
			shipname(q);
			cin >> m;
			m--;
			cout << "Select the y coordinate for your";
			shipname(q);
			cin >> l;
			l--;
		}
	}
}

//precondition: the gameboard should be initialized
//postcondition: the computer should initialize enemy coordinates y and u
void ecoord(int& y, int& u, int& q, char enarr2[][10])
{
	//creates random number btween 1 and 10 for enemy y coord and subtracts 1
	y = rand() % 10 + 1;
	y--;
	//creates random number btween 1 and 10 for enemy x coord and subtracts 1
	u = rand() % 10 + 1;
	u--;
	//checks validity of x coord
	while (u > 9 || u < 0)
	{
		u = rand() % 10 + 1;
		u--;
	}
	//checks validity of y coord
	while (y > 9 || y < 0)
	{
		y = rand() % 10 + 1;
		y--;
	}
	//check validity of both and allows computer to re input if necessary
	if (enarr2[y][u] == '#')
	{
		while (u > 9 || u < 0 || y > 9 || y < 0 || enarr2[y][u] == '#')
		{
			y = rand() % 10 + 1;
			y--;
			u = rand() % 10 + 1;
			u--;
		}
	}
}
//precondition: the play coordinates should be inputted
//postcondition: the inputted direction should be valid
void directioncheck(int& l, int& m, int q, int& b, char arr[][10], char& direct, bool& dire)
{
	//direction propt and player input
	cout << "Select direction of your ship: ";
	cin >> direct;
	//checks validity of direction
	while (direct != 'w' && direct != 'd' && direct != 's' && direct != 'a')
	{
		cout << "Not a valid direction, please try again." << endl;
		cout << "Select direction of your ship:";
		cin >> direct;
	}
	//while statempent executes while b!= the ship size and dire is still false
	while (b != shipsize(q) && dire != true)
	{
		//checks if the up direction inputted is valid
		if (direct == 'w')
		{
			if (arr[l][m] == '#' || l < 0)
			{
				cout << "You cannot place your ship in this direction." << endl;
				dire = true;
			}
			l--;
		}
		//checks validityof the right direction
		if (direct == 'd')
		{
			if (arr[l][m] == '#' || m > 9)
			{
				cout << "You cannot place your ship in this direction." << endl;
				dire = true;
			}
			m++;
		}
		//checks validity of the down direction
		if (direct == 's')
		{
			if (arr[l][m] == '#' || l > 9)
			{
				cout << "You cannot place your ship in this direction." << endl;
				dire = true;
			}
			l++;
		}
		// checks validity of the left direction
		if (direct == 'a')
		{
			if (arr[l][m] == '#' || m < 0)
			{
				cout << "You cannot place your ship in this direction." << endl;
				dire = true;
			}
			m--;
		}
		//adds 1 to b
		b++;
		//if dire = true sets b = to ship size
		if (dire == true)
			b = shipsize(q);
	}
}
//precondition: enemy coordinates should be initialized
//postcondition: the enemy direction should be valid
void edirectcheck(char& direct, int q, int y, int u, char enarr2[][10], int v, bool edire)
{
	//creates random direction
	int t = rand() % 4 + 1;
	switch (t)
	{
	case 1:  direct = 'w';
		break;
	case 2:  direct = 'd';
		break;
	case 3:  direct = 's';
		break;
	case 4:  direct = 'a';
		break;
	}
	//checks the validity of the rendom direction
	while (direct != 'w' && direct != 'd' && direct != 's' && direct != 'a')
	{
		int t = rand() % 4 + 1;
		switch (t)
		{
		case 1:  direct = 'w';
			break;
		case 2:  direct = 'd';
			break;
		case 3:  direct = 's';
			break;
		case 4:  direct = 'a';
			break;
		}
	}
	//while v != the size of the ship and edire is still false this stays active
	while (v != shipsize(q) && edire == false)
	{
		//checks the validity of the inputted direction
		if (direct == 'w')
		{
			if (enarr2[y][u] == '#' || y < 0)
			{
				edire = true;
			}
			y--;
		}
		if (direct == 'd')
		{
			if (enarr2[y][u] == '#' || u > 9)
			{
				edire = true;
			}
			u++;
		}
		if (direct == 's')
		{
			if (enarr2[y][u] == '#' || y > 9)
			{
				edire = true;
			}
			y++;
		}
		if (direct == 'a')
		{
			if (enarr2[y][u] == '#' || u < 0)
			{
				edire = true;
			}
			u--;
		}
		v++;
		if (edire == true)
			v = shipsize(q);
	}
}
//precondition: q should be initialized
//postcontition: the ship's name should be outputted
void shipname(int q)
{
	//switch statement that decides name of ship
	switch (q)
	{
	case 1:  cout << " destroyer:";
		break;
	case 2:  cout << " submarine:";
		break;
	case 3:  cout << " cruiser:";
		break;
	case 4:  cout << " battleship:";
		break;
	case 5:  cout << " carrier:";
		break;
	}
}
//precondition: display of some kind is displayed to screen
//postcondition: clears display
void clear()
{
	//prompt to press enter to clear display
	cout << endl << "Press the Enter key to continue." << endl;
	cin.ignore();
	system("CLS");
}
//precondition: player must have won or surrendered or the computer won the game
//postcondition: the game either starts again or the program ends
void endgame(char& play, bool& playagain, bool sur, int hit, int ehit, int& win, int& lose, int& surrend)
{
	//if player won, counts one win and congratulates player
	if (hit == 17)
	{
		cout << "Great Job! You've Won!" << endl;
		win++;
	}
	//if player losty, counts one lose and outputs lose sentence
	if (ehit == 17)
	{
		cout << "You've just lost. Sorry cheif." << endl;
		lose++;
	}
	//prompt for user to play again
	cout << "Would you like to play again?" << endl << "Press 'y' to play again or 'n' to exit the game." << endl;
	//user input to play again
	cin >> play;
	//checks validity of the users inputted letter if not n or y user inputs again
	if (play != 'Y' && play != 'y' && play != 'N' && play != 'n')
	{
		while (play != 'Y' && play != 'y' && play != 'N' && play != 'n')
		{
			cout << "Not a valid input, please try again." << endl;
			cout << "Press 'y' to play again or 'n' to exit the game." << endl;
			cin >> play;
		}
	}
	//if user inputted y then playagian in true
	if (play == 'Y' || play == 'y')
	{
		playagain = true;
	}
	//ing user inputted n then the playagain is false
	else if (play == 'N' || play == 'n')
	{
		playagain = false;
	}
	//if the user surrendered then adds to surrend and lose
	if (sur == true)
	{
		lose++;
		surrend++;
	}
	cout << endl << endl;
	//displays wins, loses and surrenders
	cout << "      Total Wins: " << win << endl << endl;
	cout << "     Total Loses: " << lose << endl << endl;
	cout << "Total Surrenders: " << surrend << endl << endl;
}