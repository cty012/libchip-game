#pragma once

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
 * @param column The column state to initialize.
 * @param n_tokens Number of tokens per column.
 */
void column_state_init(ColumnState* column, size_t n_tokens);

/**
 * Destructor of ColumnState.
 * @param column The column state to destroy.
 */
void column_state_free(ColumnState* column);

/**
 * Game state class.
 */
typedef struct {
    Vector columns;
    size_t n_columns;
} GameState;

/**
 * Constructor of GameState.
 * @param game The game state to initialize.
 * @param n_columns Number of columns.
 * @param n_tokens Number of tokens per column.
 */
void game_state_init(GameState* game, size_t n_columns, size_t n_tokens);

/**
 * Destructor of GameState.
 * @param game The game state to destroy.
 */
void game_state_free(GameState* game);
