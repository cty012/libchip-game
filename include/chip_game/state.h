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
 * Destructor of ColumnState.
 * @param column_s The column state to destroy.
 */
void column_state_free(ColumnState* column_s);

/**
 * Sort the tokens in the column state from highest row to lowest row.
 * @param column_s The target column state
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
 * Game state class.
 */
typedef struct {
    Vector columns;
    size_t n_columns;
} GameState;

/**
 * Constructor of GameState.
 * @param game_s The game state to initialize.
 * @param n_columns Number of columns.
 * @param n_tokens Number of tokens per column.
 */
void game_state_init(GameState* game_s, size_t n_columns, size_t n_tokens);

/**
 * Destructor of GameState.
 * @param game_s The game state to destroy.
 */
void game_state_free(GameState* game_s);

/**
 * Sort the column states in the game state.
 * @param game_s The target game state
 */
void game_state_sort(GameState* game_s);
