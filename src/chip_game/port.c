#include <chip_game/port.h>

void dealloc(void* ptr) {
    free(ptr);
}

void* column_state_alloc() {
    return malloc(sizeof(ColumnState));
}

void* game_state_alloc() {
    return malloc(sizeof(GameState));
}
