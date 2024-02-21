#include <chip_game/state.h>

void column_state_init(ColumnState* column, size_t size) {
    column->n_tokens = size;
    vector_init(&column->tokens, sizeof(int));
}

void column_state_free(ColumnState* column) {
    vector_free(&column->tokens);
    column->n_tokens = 0;
}

void game_state_init(GameState* game, size_t n_columns, size_t n_tokens) {
    // Initialize the game
    game->n_columns = n_columns;
    vector_init(&game->columns, sizeof(ColumnState));
    // Initialize the columns
    vector_reserve(&game->columns, n_columns);
    for (int i = 0; i < n_columns; i++) {
        // No need to free column since it is moved into game->columns
        ColumnState column;
        column_state_init(&column, n_tokens);
        vector_push_back(&game->columns, &column);
    }
}

void game_state_free(GameState* game) {
    // Free each column
    for (int i = 0; i < game->n_columns; i++) {
        column_state_free(vector_at(&game->columns, i));
    }
    // Free the game itself
    vector_free(&game->columns);
    game->n_columns = 0;
}
