#include <chip_game/state.h>

void column_state_init(ColumnState* column_s, size_t size) {
    column_s->n_tokens = size;
    vector_init(&column_s->tokens, sizeof(int));
}

void column_state_free(ColumnState* column_s) {
    vector_free(&column_s->tokens);
    column_s->n_tokens = 0;
}

void column_state_sort(ColumnState* column_s) {
    vector_sort(&column_s->tokens, compare_int_dec);
}

bool column_state_leq(const ColumnState* column_s1, const ColumnState* column_s2) {
    bool ans = true;
    for (size_t i = 0; i < column_s1->n_tokens || i < column_s2->n_tokens; i++) {
        int row1 = i < column_s1->n_tokens ? *(int*)vector_at(&column_s1->tokens, i) : -1;
        int row2 = i < column_s2->n_tokens ? *(int*)vector_at(&column_s2->tokens, i) : -1;
        if (row1 > row2) ans = false;
    }
    return ans;
}

void game_state_init(GameState* game_s, size_t n_columns, size_t n_tokens) {
    // Initialize the game
    game_s->n_columns = n_columns;
    vector_init(&game_s->columns, sizeof(ColumnState));
    // Initialize the columns
    vector_reserve(&game_s->columns, n_columns);
    for (int i = 0; i < n_columns; i++) {
        // No need to free column since it is moved into game->columns
        ColumnState column;
        column_state_init(&column, n_tokens);
        vector_push_back(&game_s->columns, &column);
    }
}

void game_state_free(GameState* game_s) {
    // Free each column
    for (int i = 0; i < game_s->n_columns; i++) {
        column_state_free(vector_at(&game_s->columns, i));
    }
    // Free the game itself
    vector_free(&game_s->columns);
    game_s->n_columns = 0;
}

void game_state_sort(GameState* game_s) {
    for (int i = 0; i < game_s->n_columns; i++) {
        column_state_sort(vector_at(&game_s->columns, i));
    }
}
