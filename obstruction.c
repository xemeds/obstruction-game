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
	printf(CLI_RESET CLI_BOLD "The game is played on a grid. ");
	printf("First player is " CLI_BOLD_BLUE "X" CLI_RESET CLI_BOLD " and the second player is " CLI_BOLD_RED "O" CLI_RESET CLI_BOLD ". ");
	printf("Both of the players take turns writing their symbols in a cell. ");
	printf("When a player writes their symbol in a cell, the neighbours are blocked and the other player is not able to play on the blocked cells. ");
	printf("The goal of the game is to block all the cells and leave no place for the other player to move.\n");
	printf("Further explanation: www.papg.com/show?2XMX\n\n");
	printf(CLI_BOLD_YELLOW "To write your symbol in a cell you must specify the location.\n");
	printf(CLI_BOLD_YELLOW "Ex:");
	printf(CLI_RESET CLI_BOLD " a1 c4 b6\n\n");
}

// Asks if the user wants to play against the bot or not
bool get_play_against_bot() {
	char input[2];

	printf(CLI_BOLD);
	printf("Do you want to play against the bot? [Y/n]: ");

	scanf("%1s", input);
	
	// If the input is the letter Y
	if (input[0] == 'Y' || input[0] == 'y') {
		// Return true
		return true;
	}
	// Else
	else {
		// Return false
		return false;
	}
}

// Asks if the user is the starting player or not
bool get_user_starts() {
	char input[2];

	printf(CLI_BOLD);
	printf("Do you want to be the starting player? [Y/n]: ");

	scanf("%1s", input);
	
	// If the input is the letter Y
	if (input[0] == 'Y' || input[0] == 'y') {
		// Return true
		return true;
	}
	// Else
	else {
		// Return false
		return false;
	}
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
bool terminal_state(BoardState board[][BOARD_SIZE]) {
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

// Returns the winner of the board
BoardState get_winner(BoardState board[][BOARD_SIZE]) {
	BoardState player = get_player(board);
	if (player == PLAYER_X)
		return PLAYER_O;
	else if (player == PLAYER_O)
		return PLAYER_X;
}

// Returns the player who has the next turn on the board
BoardState get_player(BoardState board[][BOARD_SIZE]) {
	int x_count = 0, o_count = 0;
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (board[x][y] == PLAYER_X)
				x_count++;
			else if (board[x][y] == PLAYER_O)
				o_count++;
		}
	}

	if (x_count > o_count)
		return PLAYER_O;
	return PLAYER_X;
}

// Places a move on the board
void place_move(BoardState board[][BOARD_SIZE], BoardState player, int x, int y) {
	// Place the neighbors
	for (int i = MAX(y - 1, 0); i < MIN(y + 2, BOARD_SIZE); i++) {
		for (int j = MAX(x - 1, 0); j < MIN(x + 2, BOARD_SIZE); j++) {
			board[i][j] = BLOCKED;
		}
	}

	// Place the symbol
	board[y][x] = player;
}

// Gets a valid user input and places it on the board
void user_move(BoardState board[][BOARD_SIZE]) {
	char move[3];
	int x, y;

	BoardState player = get_player(board);

	// Loop untill a valid move is given
	while (1)
	{
		// Get the move
		if (player == PLAYER_X)
			printf("\t\t\t    Player " CLI_BOLD_BLUE "X" CLI_RESET CLI_BOLD " > ");
		else if (player == PLAYER_O)
			printf("\t\t\t    Player " CLI_BOLD_RED "O" CLI_RESET CLI_BOLD " > ");
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
	place_move(board, get_player(board), x, y);
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
	place_move(board, get_player(board), x, y);
}

// Prints the winner of the board
void print_winner(BoardState board[][BOARD_SIZE]) {
	printf(CLI_BOLD_YELLOW);
	if (get_winner(board) == PLAYER_X)
		printf("\t\t\t\t  PLayer X wins.\n\n");
	else if (get_winner(board) == PLAYER_O)
		printf("\t\t\t\t  PLayer O wins.\n\n");
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
