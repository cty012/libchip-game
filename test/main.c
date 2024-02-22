#include <stdio.h>
#include <chip_game/map.h>
#include <chip_game/state.h>

#define N_COLS 4
#define N_TOKS 3

void test_state() {
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
    char* str1 = game_state_to_str(&game_s);
    printf("%s\n", str1);
    game_state_sort(&game_s);
    printf("After sorting:\n");
    char* str2 = game_state_to_str(&game_s);
    printf("%s\n", str2);

    // Release resources
    free(str1);
    free(str2);
    game_state_free(&game_s);
    for (size_t i = 0; i < N_COLS; i++) {
        free(arr[i]);
    }
    free(arr);
}

void test_map() {
    HashMap map;
    hashmap_init(&map);

    hashmap_insert(&map, "key1", "1");
    hashmap_insert(&map, "key2", "2");

    printf("The value for 'key1' is %s\n", (char*)hashmap_at(&map, "key1"));
    printf("The value for 'key2' is %s\n", (char*)hashmap_at(&map, "key2"));

    hashmap_remove(&map, "key1");

    printf("After deleting, the value for 'key1' is %s\n", (char*)hashmap_at(&map, "key1"));

    hashmap_free(&map);
}

int main() {
    test_map();
    return 0;
}
