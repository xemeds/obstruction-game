// Author: Muhammed Ali Dilek (xemeds)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define BOARD_SIZE 6

typedef enum eBoardState {
	FREE,
	PLAYER_X,
	PLAYER_O,
	BLOCKED
} BoardState;

BoardState board[BOARD_SIZE][BOARD_SIZE];

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
			board[y][x] = FREE;
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
			switch(board[y][x]) {
				case PLAYER_X:
					printf("\033[34m\033[1m X ");
					break;
				case PLAYER_O:
					printf("\033[31m\033[1m O ");
					break;
				case FREE:
					printf("\033[0m\033[1m   ");
					break;
				case BLOCKED:
					printf("\033[0m\033[1m # ");
					break;
			}
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
			if (board[y][x] == FREE)
				can_play = 1;
		}
	}
	return can_play;
}

// Places a move on the board
void place_move(char symbol, int x, int y) {
	// Place the neighbors
	// By Reddit user btwiusearch
	for (int i = MAX(y - 1, 0); i < MIN(y + 2, BOARD_SIZE); i++) {
		for (int j = MAX(x - 1, 0); j < MIN(x + 2, BOARD_SIZE); j++) {
			board[i][j] = BLOCKED;
		}
	}

	// Place the symbols
	if (symbol == 'X') 
		board[y][x] = PLAYER_X;

	if (symbol == 'O')
		board[y][x] = PLAYER_O;
}

// Gets a valid user input and sends it to be placed on the board
void user_move() {
	char move[3];
	int x, y;

	// Loop untill a valid move is given
	while (1)
	{
		// Get the move
		printf("\t\t\t\t\t> ");
		scanf("%2s", move);

		// Check the syntax
		int len = strlen(move);
		if (!(len == 2) || !('a' <= move[0] && move[0] <= 'f') || !('1' <= move[1] && move[1] <= '6'))
		{
			print_board();
			continue;
		}

		// Convert the move into integers
		// By Reddit user timeforscience
		x = move[0] - 'a';
		y = move[1] - '1';

		// Check if the moves location is empty
		if (board[y][x] != FREE)
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
			if (board[j][i] == FREE)
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
			if (board[j][i] == FREE)
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
