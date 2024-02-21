#include <chip_game/port.h>

void* column_state_alloc() {
    return malloc(sizeof(ColumnState));
}

void column_state_dealloc(ColumnState* column_s) {
    free(column_s);
}

void* game_state_alloc() {
    return malloc(sizeof(GameState));
}

void game_state_dealloc(GameState* game_s) {
    free(game_s);
}
