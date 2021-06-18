#ifndef MINIMAX_H
#define MINIMAX_H
#include "obstruction.h"

// Prototypes
int get_max_values_index(int array[], int size);
int get_min_values_index(int array[], int size);
void free_2d_array(int **array, int size);
int **get_moves(BoardState **board);
BoardState **get_board_of_move(BoardState **board, int x, int y);
int utility(BoardState **board);
int max_value(BoardState **board, int alpha, int beta);
int min_value(BoardState **board, int alpha, int beta);
void minimax(BoardState **board);

#endif // MINIMAX_H
