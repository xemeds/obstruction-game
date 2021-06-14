// Author: Muhammed Ali Dilek (xemeds)

#include "obstruction.h"

int main () {

	BoardState board[BOARD_SIZE][BOARD_SIZE];

	// Clear screen
	clear();

	// Print the intro
	intro();

	// Initialize the board
	init_board(board);

	// Main loop
	while (1) {
		// Game loop
		while (1)
		{
			// Print the board
			print_board(board);

			// Check if the user has places left to play
			if (!check_board(board))
			{
				print_lose();
				break;
			}

			// Users move
			user_move(board);

			// Print the board
			print_board(board);

			// Check if the bot has places left to play
			if (!check_board(board))
			{
				print_win();
				break;
			}

			// Bots move
			bot_move(board);
		}

		// If the user wants to play again
		if (play_again()) {
			// Initialize the board (reset it)
			init_board(board);

		}
		// Else if the user does not want to play again
		else {
			// Break the loop
			break;
		}
	}

	return 0;
}
