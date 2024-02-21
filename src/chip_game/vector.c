#include <stdio.h>
#include <string.h>
#include <chip_game/vector.h>

void vector_init(Vector* vector, size_t element_size) {
    vector->element_size = element_size;
    vector->size = 0;
    vector->capacity = 4;
    vector->data = malloc(vector->capacity * element_size);
}

void vector_free(Vector* vector) {
    free(vector->data);
    vector->data = NULL;
    vector->size = vector->capacity = 0;
}

void vector_push_back(Vector* vector, void* element) {
    if (vector->size == vector->capacity) {
        size_t newCapacity = vector->capacity == 0 ? 1 : vector->capacity * 2;
        void* newData = realloc(vector->data, newCapacity * vector->element_size);
        if (newData == NULL) {
            fprintf(stderr, "Failed to allocate memory\n");
            return;
        }
        vector->data = newData;
        vector->capacity = newCapacity;
    }
    memcpy((char*)vector->data + vector->size * vector->element_size, element, vector->element_size);
    vector->size++;
}

void* vector_at(Vector* vector, size_t idx) {
    if (idx >= vector->size) {
        fprintf(stderr, "Index out of range\n");
        return NULL;
    }
    return (char*)vector->data + idx * vector->element_size;
}

void vector_sort(Vector* vector, CompareFunc compare) {
    qsort(vector->data, vector->size, vector->element_size, compare);
}
