#include <stdio.h>
#include <chip_game/vector.h>

int compare_int(const void* a, const void* b) {
    const int* ia = a;
    const int* ib = b;
    return *ia - *ib;
}

int compare_int_reverse(const void* a, const void* b) {
    return -compare_int(a, b);
}

int main() {
    int numbers[] = { 7, 3, 9, 4, 6, 1, 2 };
    size_t n = sizeof(numbers) / sizeof(numbers[0]);

    Vector vector;
    vector_init(&vector, sizeof(int));
    for (size_t i = 0; i < n; i++) {
        vector_push_back(&vector, &numbers[i]);
    }

    for (size_t i = 0; i < n; i++) {
        printf("%d ", *(int *)vector_at(&vector, i));
    }
    printf("\n");

    vector_sort(&vector, &compare_int_reverse);

    for (size_t i = 0; i < n; i++) {
        printf("%d ", *(int *)vector_at(&vector, i));
    }
    printf("\n");

    return 0;
}
