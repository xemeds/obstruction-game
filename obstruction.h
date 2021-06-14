#ifndef OBSTRUCTION_H
#define OBSTRUCTION_H

#include <stdbool.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define BOARD_SIZE 6

#define CLI_RESET "\033[0m"
#define CLI_BOLD "\033[1m"
#define CLI_UNDERLINE "\033[4m"
#define CLI_CYAN "\033[36m"
#define CLI_BOLD_YELLOW "\033[1;33m"
#define CLI_BOLD_BLUE "\033[1;34m"
#define CLI_BOLD_RED "\033[1;31m"
#define CLI_BOLD_GREEN "\033[1;32m"

typedef enum eBoardState {
	FREE,
	PLAYER_X,
	PLAYER_O,
	BLOCKED
} BoardState;

// Prototypes
void clear();
void print_title();
void intro();
bool get_play_against_bot();
bool get_user_starts();
void init_board(BoardState board[][BOARD_SIZE]);
void print_board(BoardState board[][BOARD_SIZE]);
bool terminal_state(BoardState board[][BOARD_SIZE]);
BoardState get_winner(BoardState board[][BOARD_SIZE]);
BoardState get_player(BoardState board[][BOARD_SIZE]);
void place_move(BoardState board[][BOARD_SIZE], BoardState player, int x, int y);
void user_move(BoardState board[][BOARD_SIZE]);
void bot_move(BoardState board[][BOARD_SIZE]);
void print_winner(BoardState board[][BOARD_SIZE]);
bool play_again();

#endif // OBSTRUCTION_H
