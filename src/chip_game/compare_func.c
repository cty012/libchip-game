#include <chip_game/compare_func.h>

int compare_int_inc(const void* a, const void* b) {
    const int* ia = a;
    const int* ib = b;
    return *ia - *ib;
}

int compare_int_dec(const void* a, const void* b) {
    return -compare_int_inc(a, b);
}
