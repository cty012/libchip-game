from cffi import FFI


ffi = FFI()
lib = ffi.dlopen("libchip-game.dll")

ffi.cdef("""
void* column_state_alloc();
void column_state_dealloc(void* column_s);
void column_state_init(void* column_s, size_t n_tokens);
void column_state_free(void* column_s);
int column_state_get(const void* column_s, size_t tok_idx);
void column_state_set(const void* column_s, size_t tok_idx, int val);
void column_state_sort(void* column_s);
bool column_state_leq(const void* column_s1, const void* column_s2);
void column_state_print(const void* column_s);

void* game_state_alloc();
void game_state_dealloc(void* game_s);
void game_state_init(void* game_s, size_t n_columns, size_t n_tokens);
void game_state_free(void* game_s);
void* game_state_get_column(const void* game_s, size_t col_idx);
int game_state_get(const void* game_s, size_t col_idx, size_t tok_idx);
void game_state_set(const void* game_s, size_t col_idx, size_t tok_idx, int val);
void game_state_sort(void* game_s);
void game_state_print(const void* game_s);
""")


class ColumnState:
    def __init__(self, n_tokens, rows):
        self.n_tokens = n_tokens
        self.column_s = lib.column_state_alloc()
        lib.column_state_init(self.column_s, n_tokens)
        # Move data into the column state
        for i in range(n_tokens):
            lib.column_state_set(self.column_s, i, rows[i])

    def sort(self):
        lib.column_state_sort(self.column_s)

    def print(self):
        return lib.column_state_print(self.column_s)

    def __del__(self):
        lib.column_state_free(self.column_s)
        lib.column_state_dealloc(self.column_s)


class GameState:
    def __init__(self, n_columns, n_tokens, rows):
        self.n_columns = n_columns
        self.game_s = lib.game_state_alloc()
        lib.game_state_init(self.game_s, n_columns, n_tokens)
        # Move data into the game state
        for i in range(n_columns):
            for j in range(n_tokens):
                lib.game_state_set(self.game_s, i, j, rows[i][j])

    def sort(self):
        lib.game_state_sort(self.game_s)

    def print(self):
        return lib.game_state_print(self.game_s)

    def __del__(self):
        lib.game_state_free(self.game_s)
        lib.game_state_dealloc(self.game_s)
