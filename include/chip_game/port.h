#include <chip_game/state.h>

/**
 * Wrapper around `void free(void*)`.
 * @param ptr Pointer to memory to be released.
 */
void dealloc(void* ptr);

/**
 * Allocate memory for the ColumnState struct.
 * @return Pointer to the allocated memory.
 */
void* column_state_alloc();

/**
 * Allocate memory for the GameState struct.
 * @return Pointer to the allocated memory.
 */
void* game_state_alloc();
