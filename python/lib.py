from cffi import FFI
import platform


if platform.system() == "Windows":
    lib_name = "libchip_game.dll"
elif platform.system() == "Darwin":
    lib_name = "libchip_game.dylib"
else:  # Assuming Linux
    lib_name = "libchip_game.so"

ffi = FFI()
lib = ffi.dlopen(lib_name)

ffi.cdef("""
void dealloc(void*);
void* column_state_alloc();
void* game_state_alloc();

void column_state_init(void*, size_t);
void column_state_free(void*);
int column_state_get(const void*, size_t);
void column_state_set(const void*, size_t, int);
void column_state_sort(void* column_s);
bool column_state_leq(const void*, const void*);
char* column_state_to_str(const void*);

void game_state_init(void*, size_t, size_t);
void game_state_free(void*);
void* game_state_get_column(const void*, size_t);
int game_state_get(const void*, size_t, size_t);
void game_state_set(const void*, size_t, size_t, int);
void game_state_sort(void*);
char* game_state_to_str(const void*);
""")
