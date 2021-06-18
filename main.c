// Author: Muhammed Ali Dilek (xemeds)

#include <stdio.h>
#include "obstruction.h"
#include "minimax.h"

int main () {

	BoardState **board = get_board();

	// Clear screen
	clear();

	// Print the intro
	intro();

	// Get the options
	bool play_against_bot = get_play_against_bot();
	bool user_starts = false;
	bool bot_has_started = false;
	if (play_against_bot) {
		user_starts = get_user_starts();
	}

	// Main loop
	while (1) {
		// Game loop
		while (1)
		{
			// If the user is playing against the bot and does not want to start first and the bot has not started (first move for the bot)
			if (play_against_bot && !user_starts && !bot_has_started)
			{
				// Print the board
				print_board(board);

				// Bots move (calculating the first state takes time, so just place at 0, 0 which is a winning move for X)
				place_move(board, get_player(board), 0, 0);

				// Set bot has started to true
				bot_has_started = true;
			}

			// Print the board
			print_board(board);

			// Check if the user has places left to play
			if (terminal_state(board))
			{
				print_winner(board);
				break;
			}

			// Users move
			user_move(board);

			// If the user is playing against the bot
			if (play_against_bot) {
				// Print the board
				print_board(board);

				// Check if the bot has places left to play
				if (terminal_state(board))
				{
					print_winner(board);
					break;
				}

				print_bot_is_thinking();

				// Bots move
				minimax(board);
			}
		}

		// If the user wants to play again
		if (play_again()) {
			// Reset the board
			reset_board(board);

			// If the user was playing against the bot and didnt want to start first
			if (play_against_bot && !user_starts)
			{
				// Set bot has started to false
				bot_has_started = false;
			}

		}
		// Else if the user does not want to play again
		else {
			// Free the board
			free_board(board);

			// Break the loop
			break;
		}
	}

	return 0;
}
