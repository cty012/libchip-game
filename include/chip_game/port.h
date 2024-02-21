#include <chip_game/state.h>

/**
 * Allocate memory for the ColumnState struct.
 * @return Pointer to the allocated memory.
 */
void* column_state_alloc();

/**
 * Deallocate memory for the ColumnState struct.
 * @param column_s The column state to deallocate.
 */
void column_state_dealloc(ColumnState* column_s);

/**
 * Allocate memory for the GameState struct.
 * @return Pointer to the allocated memory.
 */
void* game_state_alloc();

/**
 * Deallocate memory for the GameState struct.
 * @param game_s The game state to deallocate.
 */
void game_state_dealloc(GameState* game_s);
