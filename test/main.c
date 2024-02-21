#include <stdio.h>
#include <chip_game/state.h>

#define N_COLS 4
#define N_TOKS 3

int main() {
    // Initialize 2D array
    int data[N_COLS][N_TOKS] = {
            {-1, 7, 4},
            {3, 4, 3},
            {6, 3, -1},
            {-1, -1, 0}};

    int** arr = malloc(sizeof(int*) * N_COLS);
    for (size_t i = 0; i < N_COLS; i++) {
        arr[i] = malloc(sizeof(int*) * N_TOKS);
        for (size_t j = 0; j < N_TOKS; j++) {
            arr[i][j] = data[i][j];
        }
    }

    // Game state
    GameState game_s;
    game_state_init_from_arr(&game_s, N_COLS, N_TOKS, arr);

    printf("Before sorting:\n");
    game_state_print(&game_s);
    game_state_sort(&game_s);
    printf("After sorting:\n");
    game_state_print(&game_s);

    // Release resources
    game_state_free(&game_s);
    for (size_t i = 0; i < N_COLS; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
