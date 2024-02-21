#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <chip_game/vector.h>

/**
 * Column state class.
 */
typedef struct {
    Vector tokens;
    size_t n_tokens;
} ColumnState;

/**
 * Constructor of ColumnState.
 * @param column_s The column state to initialize.
 * @param n_tokens Number of tokens per column.
 */
void column_state_init(ColumnState* column_s, size_t n_tokens);

/**
 * Constructor of ColumnState.
 * @param column_s The column state to initialize.
 * @param n_tokens Number of tokens per column.
 * @param arr 1D array that stores the row number of each token.
 */
void column_state_init_from_arr(ColumnState* column_s, size_t n_tokens, int* arr);

/**
 * Destructor of ColumnState.
 * @param column_s The column state to destroy.
 */
void column_state_free(ColumnState* column_s);

/**
 * Get the row number of a token. Returns -1 for invalid indices.
 * @param column_s The target column state.
 * @param tok_idx Index of the token.
 * @return Row number of the token.
 */
int column_state_get(const ColumnState* column_s, size_t tok_idx);

/**
 * Set the row number of a token. No nothing for invalid indices.
 * @param column_s The target column state.
 * @param tok_idx Index of the token.
 * @param val New row number of the token.
 */
void column_state_set(const ColumnState* column_s, size_t tok_idx, int val);

/**
 * Sort the tokens in the column state from highest row to lowest row.
 * @param column_s The target column state.
 */
void column_state_sort(ColumnState* column_s);

/**
 * Compares two column states according to a partial order. Only call this function on sorted column states!!!
 * @param column_s1 The first SORTED column state.
 * @param column_s2 The second SORTED column state.
 * @return Whether the first column state is less than or equal to the second.
 *
 * If the two column states have different number of tokens, will fill the shorter column with -1.
 */
bool column_state_leq(const ColumnState* column_s1, const ColumnState* column_s2);

/**
 * Prints the content of the game state to the console.
 * @param column_s The target column state.
 * @return String representation of the game state.
 */
char* column_state_to_str(const ColumnState* column_s);

/**
 * Game state class.
 */
typedef struct {
    Vector columns;
    size_t n_columns;
    size_t n_tokens;
} GameState;

/**
 * Constructor of GameState.
 * @param game_s The game state to initialize.
 * @param n_columns Number of columns.
 * @param n_tokens Number of tokens per column.
 */
void game_state_init(GameState* game_s, size_t n_columns, size_t n_tokens);

/**
 * Constructor of GameState.
 * @param game_s The game state to initialize.
 * @param n_columns Number of columns.
 * @param n_tokens Number of tokens per column.
 * @param rows 2D array that stores the row number of each token.
 */
void game_state_init_from_arr(GameState* game_s, size_t n_columns, size_t n_tokens, int** rows);

/**
 * Destructor of GameState.
 * @param game_s The game state to destroy.
 */
void game_state_free(GameState* game_s);

/**
 * Get the column state stored in the game state.
 * @param game_s The target game state.
 * @param col_idx Column number of the token.
 * @return Column state stored in the game state.
 */
ColumnState* game_state_get_column(const GameState* game_s, size_t col_idx);

/**
 * Get the row number of a token. Returns -1 for invalid indices.
 * @param game_s The target game state.
 * @param col_idx Column number of the token.
 * @param tok_idx Index of the token.
 * @return Row number of the token.
 */
int game_state_get(const GameState* game_s, size_t col_idx, size_t tok_idx);

/**
 * Set the row number of a token. No nothing for invalid indices.
 * @param game_s The target game state.
 * @param col_idx Column number of the token.
 * @param tok_idx Index of the token.
 * @param val New row number of the token.
 */
void game_state_set(const GameState* game_s, size_t col_idx, size_t tok_idx, int val);

/**
 * Sort the column states in the game state.
 * @param game_s The target game state.
 */
void game_state_sort(GameState* game_s);

/**
 * Prints the content of the game state to the console.
 * @param game_s The target game state.
 * @return String representation of the game state.
 */
char* game_state_to_str(const GameState* game_s);
