from lib import ffi as _ffi, lib as _lib


class ColumnState:
    def __init__(self, n_tokens, rows):
        self.n_tokens = n_tokens
        self.column_s = _lib.column_state_alloc()
        _lib.column_state_init(self.column_s, n_tokens)
        # Move data into the column state
        for i in range(n_tokens):
            _lib.column_state_set(self.column_s, i, rows[i])

    def sort(self):
        _lib.column_state_sort(self.column_s)

    def __str__(self):
        cstr = _lib.column_state_to_str(self.column_s)
        pystr = _ffi.string(cstr).decode("utf-8")
        _lib.dealloc(cstr)
        return pystr
    __repr__ = __str__

    def __del__(self):
        _lib.column_state_free(self.column_s)
        _lib.dealloc(self.column_s)


class ColumnStateReference:
    def __init__(self, game_s, col_idx):
        self.game_s = game_s
        self.column_s = _lib.game_state_get_column(game_s, col_idx)
        self.col_idx = col_idx

    def sort(self):
        _lib.column_state_sort(self.column_s)


class GameState:
    def __init__(self, n_columns, n_tokens, rows):
        self.n_columns = n_columns
        self.game_s = _lib.game_state_alloc()
        _lib.game_state_init(self.game_s, n_columns, n_tokens)
        # Move data into the game state
        for i in range(n_columns):
            for j in range(n_tokens):
                _lib.game_state_set(self.game_s, i, j, rows[i][j])

    def sort(self):
        _lib.game_state_sort(self.game_s)

    def __str__(self):
        cstr = _lib.game_state_to_str(self.game_s)
        pystr = _ffi.string(cstr).decode("utf-8")
        _lib.dealloc(cstr)
        return pystr
    __repr__ = __str__

    def __del__(self):
        _lib.game_state_free(self.game_s)
        _lib.dealloc(self.game_s)
