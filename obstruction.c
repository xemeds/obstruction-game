#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "obstruction.h"

// Clears the screen
void clear() {
	system("clear");
}

// Prints the ASCII art title
void print_title() {
	printf(CLI_CYAN);
	printf("\n");
	printf("\t      █▀▀█ █▀▀▄ █▀▀ ▀▀█▀▀ █▀▀█ █░░█ █▀▀ ▀▀█▀▀ ░▀░ █▀▀█ █▀▀▄\n");
	printf("\t      █░░█ █▀▀▄ ▀▀█ ░░█░░ █▄▄▀ █░░█ █░░ ░░█░░ ▀█▀ █░░█ █░░█\n");
	printf("\t      ▀▀▀▀ ▀▀▀░ ▀▀▀ ░░▀░░ ▀░▀▀ ░▀▀▀ ▀▀▀ ░░▀░░ ▀▀▀ ▀▀▀▀ ▀░░▀\n\n");
	printf(CLI_RESET CLI_BOLD);
}

// Introduction to the game
void intro() {
	// ASCII art title
	print_title();

	// Intro
	printf(CLI_BOLD_YELLOW CLI_UNDERLINE "\n\nDescription:\n");
	printf(CLI_RESET CLI_BOLD "The game is played on a grid of 6 x 6. ");
	printf("Your symbol is '" CLI_BOLD_BLUE "X" CLI_RESET CLI_BOLD "' and the bots symbol is '" CLI_BOLD_RED "O" CLI_RESET CLI_BOLD "'. ");
	printf("You and the bot take turns writing your symbols in a cell. The restriction is that you can only play in a cell if all its neighbours are empty.\n");
	printf("Further explanation: www.papg.com/show?2XMX\n\n");
	printf(CLI_BOLD_YELLOW CLI_UNDERLINE "Goal:" CLI_RESET CLI_BOLD " Leave no place for the bot to move.\n\n");
	printf(CLI_BOLD_YELLOW "To write your symbol in a cell you must specify the location.\n");
	printf(CLI_BOLD_YELLOW "Ex:");
	printf(CLI_RESET CLI_BOLD " a1 c4 b6\n\n");

	// Start
	printf("Press enter to start...\n");
	printf("> ");
	getchar();
}

// Initializes the board
void init_board(BoardState board[][BOARD_SIZE]) {
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			board[y][x] = FREE;
		}
	}
}

// Prints the board
void print_board(BoardState board[][BOARD_SIZE]) {
	clear();
	printf(CLI_RESET);
	print_title();
	printf("\t\t\t      a   b   c   d   e   f\n");
	printf(CLI_BOLD_GREEN);
	printf("\t\t\t    ╔═══╤═══╤═══╤═══╤═══╤═══╗\n");
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		printf(CLI_RESET CLI_BOLD);
		printf("\t\t\t  %i ", y + 1);
		printf(CLI_BOLD_GREEN "║");
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			switch(board[y][x]) {
				case PLAYER_X:
					printf(CLI_BOLD_BLUE " X ");
					break;
				case PLAYER_O:
					printf(CLI_BOLD_RED " O ");
					break;
				case FREE:
					printf("   ");
					break;
				case BLOCKED:
					printf(CLI_RESET CLI_BOLD " # ");
					break;
			}
			if (x != BOARD_SIZE - 1)
				printf(CLI_BOLD_GREEN "│");
		}
		printf(CLI_BOLD_GREEN "║\n");
		if (y != BOARD_SIZE - 1)
			printf("\t\t\t    ╟───┼───┼───┼───┼───┼───╢\n");
	}
	printf("\t\t\t    ╚═══╧═══╧═══╧═══╧═══╧═══╝\n\n");
	printf(CLI_RESET CLI_BOLD);
	printf("\t\t    ==+==+==+==+==+==+==+==+==+==+==+==+==+==\n\n");
}

// Returns true if there is a place left to play on the board, else returns false
bool check_board(BoardState board[][BOARD_SIZE]) {
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board[y][x] == FREE)
				return true;
		}
	}
	return false;
}

// Places a move on the board
void place_move(BoardState board[][BOARD_SIZE], char symbol, int x, int y) {
	// Place the neighbors
	for (int i = MAX(y - 1, 0); i < MIN(y + 2, BOARD_SIZE); i++) {
		for (int j = MAX(x - 1, 0); j < MIN(x + 2, BOARD_SIZE); j++) {
			board[i][j] = BLOCKED;
		}
	}

	// Place the symbol
	if (symbol == 'X') 
		board[y][x] = PLAYER_X;

	if (symbol == 'O')
		board[y][x] = PLAYER_O;
}

// Gets a valid user input and places it on the board
void user_move(BoardState board[][BOARD_SIZE]) {
	char move[3];
	int x, y;

	// Loop untill a valid move is given
	while (1)
	{
		// Get the move
		printf("\t\t\t\t     > ");
		scanf("%2s", move);

		// Check the syntax
		int len = strlen(move);
		if (!(len == 2) || !('a' <= move[0] && move[0] <= 'f') || !('1' <= move[1] && move[1] <= '6'))
		{
			print_board(board);
			continue;
		}

		// Convert the move into integers
		x = move[0] - 'a';
		y = move[1] - '1';

		// Check if the moves location is empty
		if (board[y][x] != FREE)
		{
			print_board(board);
			continue;
		}

		// Break the loop
		break;
	}

	// Place the move
	place_move(board, 'X', x, y);
}

// Chooses a random empty cell and sends it to be placed on the board
void bot_move(BoardState board[][BOARD_SIZE]) {
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
	place_move(board, 'O', x, y);
}

// Prints the win message
void print_win() {
	printf(CLI_BOLD_YELLOW);
	printf("\t\t\t\t     You win.\n\n");
	printf(CLI_RESET);
}

// Prints the lose message
void print_lose() {
	printf(CLI_BOLD_YELLOW);
	printf("\t\t\t\t     You lose.\n\n");
	printf(CLI_RESET);
}

// Checks if the user wants to play again
bool play_again() {
	char input[2];

	printf(CLI_BOLD);
	printf("\t\t\t\t    R - Replay\n");
	printf("\t\t\t\t    Q - Quit\n\n");
	printf("\t\t\t\t     > ");

	scanf("%1s", input);
	
	// If the input is the letter R
	if (input[0] == 'R' || input[0] == 'r') {
		// Return true
		return true;
	}
	// Else
	else {
		// Return false
		return false;
	}
}
