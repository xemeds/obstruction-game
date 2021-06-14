// Author: Muhammed Ali Dilek (xemeds)

#include "obstruction.h"

int main () {

	BoardState board[BOARD_SIZE][BOARD_SIZE];

	// Clear screen
	clear();

	// Print the intro
	intro();

	bool play_against_bot = get_play_against_bot();
	bool user_starts;
	if (play_against_bot) {
		user_starts = get_user_starts();
	}

	// Initialize the board
	init_board(board);

	// If the user is playing against the bot and does not want to start first
	if (play_against_bot && !user_starts)
	{
		// Print the board
		print_board(board);

		// Bots move
		bot_move(board);
	}

	// Main loop
	while (1) {
		// Game loop
		while (1)
		{
			// Print the board
			print_board(board);

			// Check if the user has places left to play
			if (!terminal_state(board))
			{
				print_winner(board);
				break;
			}

			// Users move
			user_move(board);

			if (play_against_bot) {
				// Print the board
				print_board(board);

				// Check if the bot has places left to play
				if (!terminal_state(board))
				{
					print_winner(board);
					break;
				}

				// Bots move
				bot_move(board);
			}
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
