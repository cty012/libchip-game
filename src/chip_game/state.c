#include <stdio.h>
#include <string.h>
#include <chip_game/state.h>

void column_state_init(ColumnState* column_s, size_t n_tokens) {
    column_s->n_tokens = n_tokens;
    vector_init(&column_s->tokens, sizeof(int));
    int prototype = -1;
    vector_resize(&column_s->tokens, n_tokens, &prototype);
}

void column_state_init_from_arr(ColumnState* column_s, size_t n_tokens, int* arr) {
    column_s->n_tokens = n_tokens;
    vector_init_from_arr(&column_s->tokens, sizeof(int), n_tokens, arr);
}

void column_state_free(ColumnState* column_s) {
    vector_free(&column_s->tokens);
    column_s->n_tokens = 0;
}

int column_state_get(const ColumnState* column_s, size_t tok_idx) {
    if (tok_idx >= column_s->n_tokens) return -1;
    return *(int*)vector_at(&column_s->tokens, tok_idx);
}

void column_state_set(const ColumnState* column_s, size_t tok_idx, int val) {
    if (tok_idx >= column_s->n_tokens) return;
    *(int*)vector_at(&column_s->tokens, tok_idx) = val;
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

char* column_state_to_str(const ColumnState* column_s) {
    Vector buffer;
    vector_init_from_arr(&buffer, sizeof(char), 1, "[");
    for (size_t i = 0; i < column_s->n_tokens; i++) {
        if (i) {
            vector_push_back_arr(&buffer, 2, ", ");
        }
        char num[12];
        int digits = snprintf(num, sizeof(num), "%d", column_state_get(column_s, i));
        vector_push_back_arr(&buffer, digits, num);
    }
    vector_push_back_arr(&buffer, 2, "]");
    // Extract the string
    char* str = strdup(buffer.data);
    vector_free(&buffer);
    return str;
}

void game_state_init(GameState* game_s, size_t n_columns, size_t n_tokens) {
    // Initialize the game
    game_s->n_columns = n_columns;
    game_s->n_tokens = n_tokens;
    vector_init(&game_s->columns, sizeof(ColumnState));
    // Initialize the columns
    vector_reserve(&game_s->columns, n_columns);
    for (size_t i = 0; i < n_columns; i++) {
        // No need to free column since it is moved into game->columns
        ColumnState column;
        column_state_init(&column, n_tokens);
        vector_push_back(&game_s->columns, &column);
    }
}

void game_state_init_from_arr(GameState* game_s, size_t n_columns, size_t n_tokens, int** rows) {
    // Initialize the game
    game_s->n_columns = n_columns;
    game_s->n_tokens = n_tokens;
    vector_init(&game_s->columns, sizeof(ColumnState));
    // Initialize the columns
    vector_reserve(&game_s->columns, n_columns);
    for (size_t i = 0; i < n_columns; i++) {
        // No need to free column since it is moved into game->columns
        ColumnState column;
        column_state_init_from_arr(&column, n_tokens, rows[i]);
        vector_push_back(&game_s->columns, &column);
    }
}

void game_state_free(GameState* game_s) {
    // Free each column
    for (size_t i = 0; i < game_s->n_columns; i++) {
        column_state_free(game_state_get_column(game_s, i));
    }
    // Free the game itself
    vector_free(&game_s->columns);
    game_s->n_columns = 0;
}

ColumnState* game_state_get_column(const GameState* game_s, size_t col_idx) {
    if (col_idx >= game_s->n_columns) return NULL;
    return vector_at(&game_s->columns, col_idx);
}

int game_state_get(const GameState* game_s, size_t col_idx, size_t tok_idx) {
    ColumnState* column_s = game_state_get_column(game_s, col_idx);
    if (!column_s) return -1;
    return column_state_get(column_s, tok_idx);
}

void game_state_set(const GameState* game_s, size_t col_idx, size_t tok_idx, int val) {
    ColumnState* column_s = game_state_get_column(game_s, col_idx);
    if (!column_s) return;
    column_state_set(column_s, tok_idx, val);
}

void game_state_sort(GameState* game_s) {
    for (size_t i = 0; i < game_s->n_columns; i++) {
        column_state_sort(game_state_get_column(game_s, i));
    }
}

char* game_state_to_str(const GameState* game_s) {
    Vector buffer;
    vector_init_from_arr(&buffer, sizeof(char), 1, "[");
    for (size_t i = 0; i < game_s->n_tokens; i++) {
        if (i) vector_push_back_arr(&buffer, 2, "\n ");
        char* column_str = column_state_to_str(game_state_get_column(game_s, i));
        vector_push_back_arr(&buffer, strlen(column_str), column_str);
        free(column_str);
    }
    vector_push_back_arr(&buffer, 2, "]");
    // Extract the string
    char* str = strdup(buffer.data);
    vector_free(&buffer);
    return str;
}
