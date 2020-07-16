// Author: Muhammed Ali Dilek (xemeds)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 6

char board[BOARD_SIZE][BOARD_SIZE];

// Clears the screen
void clear() {
	system("clear");
}

// Prints the ASCII art
void print_art() {
	printf("\033[0;36m");
	printf("░█████╗░██████╗░░██████╗████████╗██████╗░██╗░░░██╗░█████╗░████████╗██╗░█████╗░███╗░░██╗\n");
	printf("██╔══██╗██╔══██╗██╔════╝╚══██╔══╝██╔══██╗██║░░░██║██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║\n");
	printf("██║░░██║██████╦╝╚█████╗░░░░██║░░░██████╔╝██║░░░██║██║░░╚═╝░░░██║░░░██║██║░░██║██╔██╗██║\n");
	printf("██║░░██║██╔══██╗░╚═══██╗░░░██║░░░██╔══██╗██║░░░██║██║░░██╗░░░██║░░░██║██║░░██║██║╚████║\n");
	printf("╚█████╔╝██████╦╝██████╔╝░░░██║░░░██║░░██║╚██████╔╝╚█████╔╝░░░██║░░░██║╚█████╔╝██║░╚███║\n");
	printf("░╚════╝░╚═════╝░╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝░╚═════╝░░╚════╝░░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝\n");
	printf("\033[0m\n");
}

// Introduction to the game
void intro() {
	// ASCII art
	print_art();

	// Intro
	printf("\n");
	printf("\033[33m\033[4m\033[1mDescription:\n");
	printf("\033[0m\033[1m");
	printf("\nThe game is played on a grid of 6 x 6. Your symbol is '\033[34m\033[1mX\033[0m\033[1m' and the bots symbol is '\033[31m\033[1mO\033[0m\033[1m'.\n");
	printf("You and the bot take turns writing your symbols in a cell. The restriction is that\n");
	printf("you can only play in a cell if all its neighbours are empty.\n");
	printf("Further explanation: www.papg.com/show?2XMX\n");
	printf("\n");
	printf("\033[33m\033[4m\033[1mGoal:");
	printf("\033[0m\033[1m Leave no place for the bot to move.\n");
	printf("\n");
	printf("\033[33m\033[1mTo write your symbol in a cell you must specify the location.\n");
	printf("\033[33m\033[1mEx:");
	printf("\033[0m\033[1m a1 c4 b6\n");

	// Start
	printf("\nPress Enter to start...\n");
	printf("> ");
	getchar();
}

// Initializes the board
void init_board() {
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			board[y][x] = ' ';
		}
	}
}

// Prints the board
void print_board() {
	clear();
	print_art();
	printf("\033[0m\033[1m");
	printf("\t\t\t\t  a   b   c   d   e   f\n");
	printf("\033[32m");
	printf("\t\t\t\t╔═══╤═══╤═══╤═══╤═══╤═══╗\n");
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		printf("\033[0m\033[1m");
		printf("\t\t\t      %i ", y + 1);
		printf("\033[32m║");
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board[y][x] == 'X')
				printf("\033[34m\033[1m %c ", board[y][x]);
			else if (board[y][x] == 'O')
				printf("\033[31m\033[1m %c ", board[y][x]);
			else
				printf("\033[0m\033[1m %c ", board[y][x]);
			if (x != BOARD_SIZE - 1)
				printf("\033[32m│");
		}
		printf("\033[32m║\n");
		if (y != BOARD_SIZE - 1)
			printf("\t\t\t\t╟───┼───┼───┼───┼───┼───╢\n");
	}
	printf("\t\t\t\t╚═══╧═══╧═══╧═══╧═══╧═══╝\n\n");
	printf("\033[0m\033[1m");
	printf("\t\t\t==+==+==+==+==+==+==+==+==+==+==+==+==+==\n\n");
}

// Returns 0 if there are no places left to play
int check_board() {
	int can_play = 0;
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board[y][x] == ' ')
				can_play = 1;
		}
	}
	return can_play;
}

// Places a move on the board
void place_move(char symbol, int x, int y) {
	// Place the neighbors
	// Corners
	if ((x == 0 && y == 0))
	{
		board[0][1] = '#';
		board[1][0] = '#';
		board[1][1] = '#';
	}
	else if ((x == BOARD_SIZE - 1 && y == 0))
	{
		board[0][BOARD_SIZE - 2] = '#';
		board[1][BOARD_SIZE - 1] = '#';
		board[1][BOARD_SIZE - 2] = '#';
	}
	else if ((x == 0 && y == BOARD_SIZE - 1))
	{
		board[BOARD_SIZE - 2][0] = '#';
		board[BOARD_SIZE - 1][1] = '#';
		board[BOARD_SIZE - 2][1] = '#';
	}
	else if ((x == BOARD_SIZE - 1 && y == BOARD_SIZE - 1))
	{
		board[BOARD_SIZE - 2][BOARD_SIZE - 1] = '#';
		board[BOARD_SIZE - 1][BOARD_SIZE - 2] = '#';
		board[BOARD_SIZE - 2][BOARD_SIZE - 2] = '#';
	}

	// Edges
	else if (x == 0)
	{
		for (int j = y - 1; j < y + 2; j++)
		{
			for (int i = x; i < x + 2; i++)
			{
				board[j][i] = '#';
			}
		}
	}
	else if (x == BOARD_SIZE - 1)
	{
		for (int j = y - 1; j < y + 2; j++)
		{
			for (int i = x - 1; i < x + 1; i++)
			{
				board[j][i] = '#';
			}
		}
	}
	else if (y == 0)
	{
		for (int j = y; j < y + 2; j++)
		{
			for (int i = x - 1; i < x + 2; i++)
			{
				board[j][i] = '#';
			}
		}
	}
	else if (y == BOARD_SIZE - 1)
	{
		for (int j = y - 1; j < y + 1; j++)
		{
			for (int i = x - 1; i < x + 2; i++)
			{
				board[j][i] = '#';
			}
		}
	}

	// Normal
	else
	{
		for (int j = y - 1; j < y + 2; j++)
		{
			for (int i = x - 1; i < x + 2; i++)
			{
				board[j][i] = '#';
			}
		}
	}

	// Place the symbol
	board[y][x] = symbol;
}

// Gets a valid user input and sends it to be placed on the board
void user_move() {
	char move[2];
	int x, y;

	// Loop untill a valid move is given
	while (1)
	{
		// Get the move
		printf("\t\t\t\t\t> ");
		scanf("%s", move);

		// Check the syntax
		int len = strlen(move);
		if (!(len == 2) || !(97 <= move[0] && move[0] <= 102) || !(49 <= move[1] && move[1] <= 54))
		{
			print_board();
			continue;
		}

		// Convert the move into integers
		switch(move[0]) {
			case 'a' :
				x = 0;
				break;
			case 'b' :
				x = 1;
				break;
			case 'c' :
				x = 2;
				break;
			case 'd' :
				x = 3;
				break;
			case 'e' :
				x = 4;
				break;
			case 'f' :
				x = 5;
				break;
		}
		switch(move[1]) {
			case '1' :
				y = 0;
				break;
			case '2' :
				y = 1;
				break;
			case '3' :
				y = 2;
				break;
			case '4' :
				y = 3;
				break;
			case '5' :
				y = 4;
				break;
			case '6' :
				y = 5;
				break;
		}

		// Check if the moves location is empty
		if (board[y][x] != ' ')
		{
			print_board();
			continue;
		}

		// Break the loop
		break;
	}

	// Place the move
	place_move('X', x, y);
}

// Chooses a random empty cell and sends it to be placed on the board
void bot_move() {
	int empty_cells = 0, x, y, random_cell;

	// Find the amount of empty cells
	for (int j = 0; j < BOARD_SIZE; j++)
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			if (board[j][i] == ' ')
				empty_cells++;
		}
	}

	// Choose a random empty cell
	random_cell = (999 % empty_cells) + 1;

	// Find the random empty cells location
	int cell = 0;
	for (int j = 0; j < BOARD_SIZE; j++)
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			if (board[j][i] == ' ')
			{
				cell++;
				if (cell == random_cell)
				{
					x = i;
					y = j;
				}
			}
		}
	}

	// Place the bots move on that location
	place_move('O', x, y);
}

int main () {
	// Clear screen
	clear();

	// Print the intro
	intro();

	// Initialize the board
	init_board();

	// Main loop
	while (1)
	{
		// Print the board
		print_board();

		// Check if the user has places left to play
		if (!check_board())
		{
			printf("\033[33m\033[1m\t\t\t\t\tYou lose.\033[0m\n\n");
			break;
		}

		// Users move
		user_move();

		// Print the board
		print_board();

		// Check if the bot has places left to play
		if (!check_board())
		{
			printf("\033[33m\033[1m\t\t\t\t\tYou win.\033[0m\n\n");
			break;
		}

		// Bots move
		bot_move();
	}

	return 0;
}
