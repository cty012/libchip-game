#include <stdio.h>
#include <chip_game/vector.h>

int main() {
    int numbers[] = { 7, 3, 9, 4, 6, 1, 2 };
    size_t n = sizeof(numbers) / sizeof(numbers[0]);

    Vector vector;
    vector_init(&vector, sizeof(int));
    for (size_t i = 0; i < n; i++) {
        vector_push_back(&vector, &numbers[i]);
    }

    for (size_t i = 0; i < n; i++) {
        printf("%d ", *(int*)vector_at(&vector, i));
    }
    printf("\n");

    vector_sort(&vector, &compare_int_dec);

    for (size_t i = 0; i < n; i++) {
        printf("%d ", *(int*)vector_at(&vector, i));
    }
    printf("\n");

    vector_free(&vector);

    return 0;
}
