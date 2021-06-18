#include <stdlib.h>
#include <stdio.h>
#include "minimax.h"

// X is the maximizing player, O is the minimizing player

// Returns the index of the max value of the given array
int get_max_values_index(int array[], int size) {
	int index = 0;

	for (int i = 0; i < size; i++) {
		if (array[i] > array[index])
			index = i;
	}

	return index;
}

// Returns the index of the min value of the given array
int get_min_values_index(int array[], int size) {
	int index = 0;

	for (int i = 0; i < size; i++) {
		if (array[i] < array[index])
			index = i;
	}

	return index;
}

// Frees a given 2d array
void free_2d_array(int **array, int size) {
	for (int i = 0; i < size && array[i] != NULL; i++) {
		free(array[i]);
	}

	free(array);
}

// Returns all the possible moves available on the board
int **get_moves(BoardState **board) {
	// Allocate the 2d array for the moves
	int **moves = (int **)malloc(BOARD_SIZE * BOARD_SIZE * sizeof(int *));

	// Add all the positions of the free cells on the board to the array
	int move_index = 0;
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board[y][x] == FREE) {
				moves[move_index] = (int *)malloc(2 * sizeof(int));
				moves[move_index][0] = x;
				moves[move_index][1] = y;
				move_index++;
			}
		}
	}

	// If the array is not full set the rest of the array to null
	if (move_index != BOARD_SIZE * BOARD_SIZE) {
		for (int i = move_index; i < BOARD_SIZE * BOARD_SIZE; i++) {
			moves[i] = NULL;
		}
	}

	return moves;
}

// Returns a copy of the board that results from making the given move
BoardState **get_board_of_move(BoardState **board, int x, int y) {
	// Get a new board
	BoardState **new_board = get_board();

	// Copy the cells of the given board to the new board
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			new_board[y][x] = board[y][x];
		}
	}

	// Place the given move on the new board
	place_move(new_board, get_player(new_board), x, y);

	return new_board;
}

// Returns 1 if X has won the game, -1 if O has won (there cannot be a draw)
int utility(BoardState **board) {
	BoardState winner = get_winner(board);
	if (winner == PLAYER_X)
		return 1;
	else
		return -1;
}

int max_value(BoardState **board, int alpha, int beta) {
	if (terminal_state(board))
		return utility(board);

	int value = -2;
	int **moves = get_moves(board);
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE && moves[i] != NULL; i++) {
		BoardState **new_board = get_board_of_move(board, moves[i][0], moves[i][1]);
		value = MAX(value, min_value(new_board, alpha, beta));
		free_board(new_board);
		alpha = MAX(alpha, value);
		if (beta <= alpha)
			break;
	}

	free_2d_array(moves, BOARD_SIZE * BOARD_SIZE);

	return value;
}

int min_value(BoardState **board, int alpha, int beta) {
	if (terminal_state(board))
		return utility(board);

	int value = 2;
	int **moves = get_moves(board);
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE && moves[i] != NULL; i++) {
		BoardState **new_board = get_board_of_move(board, moves[i][0], moves[i][1]);
		value = MIN(value, max_value(new_board, alpha, beta));
		free_board(new_board);
		beta = MIN(beta, value);
		if (beta <= alpha)
			break;
	}

	free_2d_array(moves, BOARD_SIZE * BOARD_SIZE);

	return value;
}

// Places the optimal move for the current player on the board
void minimax(BoardState **board) {
	int x, y;
	int **moves = get_moves(board);
	int values[BOARD_SIZE * BOARD_SIZE];
	
	if (get_player(board) == PLAYER_X) {
		int number_of_moves = 0;
		bool found_winning_move = false;
		for (int i = 0; i < BOARD_SIZE * BOARD_SIZE && moves[i] != NULL; i++) {
			BoardState **new_board = get_board_of_move(board, moves[i][0], moves[i][1]);
			// printf("TRYING MOVE: (%i, %i)\n", moves[i][0], moves[i][1]);
			values[i] = min_value(new_board, -2, 2);
			// printf("VALUE: %i\n", values[i]);
			free_board(new_board);
			number_of_moves++;

			if (values[i] == 1)
				break;
		}

		/*
		for (int i = 0; i < number_of_moves; i++) {
			printf("%i, ", values[i]);
		}
		printf("\n");
		*/
		
		int min_values_index = get_max_values_index(values, number_of_moves);
		// printf("MIN VALUES INDEX: %i\n", min_values_index);
		x = moves[min_values_index][0];
		y = moves[min_values_index][1];
	}
	else {
		int number_of_moves = 0;
		bool found_winning_move = false;
		for (int i = 0; i < BOARD_SIZE * BOARD_SIZE && moves[i] != NULL; i++) {
			BoardState **new_board = get_board_of_move(board, moves[i][0], moves[i][1]);
			// printf("TRYING MOVE: (%i, %i)\n", moves[i][0], moves[i][1]);
			values[i] = max_value(new_board, -2, 2);
			// printf("VALUE: %i\n", values[i]);
			free_board(new_board);
			number_of_moves++;

			if (values[i] == -1)
				break;
		}

		/*
		for (int i = 0; i < number_of_moves; i++) {
			printf("%i, ", values[i]);
		}
		printf("\n");
		*/

		int min_values_index = get_min_values_index(values, number_of_moves);
		// printf("MIN VALUES INDEX: %i\n", min_values_index);
		x = moves[min_values_index][0];
		y = moves[min_values_index][1];
	}

	free_2d_array(moves, BOARD_SIZE * BOARD_SIZE);

	place_move(board, get_player(board), x, y);
}
