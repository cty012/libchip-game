#include <stdio.h>
#include <string.h>
#include <chip_game/vector.h>

/**
 * Helper function that determines the new capacity to expand to.
 * @param capacity The current capacity.
 * @param target The minimum capacity to reach.
 * @return The new capacity.
 */
size_t expand_capacity(size_t capacity, size_t target) {
    while (capacity < target) {
        capacity = capacity ? capacity * 2 : 1;
    }
    return capacity;
}

void vector_init(Vector* vector, size_t element_size) {
    vector->element_size = element_size;
    vector->size = 0;
    vector->capacity = 4;
    vector->data = malloc(vector->capacity * element_size);
}

void vector_init_from_arr(Vector* vector, size_t element_size, size_t size, void* arr) {
    vector->element_size = element_size;
    vector->size = size;
    vector->capacity = expand_capacity(4, size);
    vector->data = malloc(vector->capacity * element_size);
    memcpy(vector->data, arr, vector->element_size * vector->size);
}

void vector_free(Vector* vector) {
    free(vector->data);
    vector->data = NULL;
    vector->size = vector->capacity = 0;
}

size_t vector_capacity(Vector* vector) {
    return vector->capacity;
}

int vector_reserve(Vector* vector, size_t capacity) {
    if (capacity == vector->capacity) return 0;
    if (vector->size > capacity) capacity = vector->size;
    void* newData = realloc(vector->data, capacity * vector->element_size);
    if (newData == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }
    vector->data = newData;
    vector->capacity = capacity;
    return 0;
}

size_t vector_size(Vector* vector) {
    return vector->size;
}

bool vector_empty(const Vector* vector) {
    return !vector->size;
}

int vector_resize(Vector* vector, size_t size, void* prototype) {
    // Determine the new capacity
    size_t newCapacity = expand_capacity(vector->capacity, size);
    // Update capacity
    int err = vector_reserve(vector, newCapacity);
    if (err) return err;
    // Resize
    if (size > vector->size) {
        for (size_t i = 0; i < size - vector->size; i++) {
            void* dst = (char*)vector->data + (vector->size + i) * vector->element_size;
            memcpy(dst, prototype, vector->element_size);
        }
    }
    vector->size = size;
    return 0;
}

int vector_push_back(Vector* vector, void* ptr_to_element) {
    return vector_resize(vector, vector->size + 1, ptr_to_element);
}

int vector_push_back_arr(Vector* vector, size_t count, void* arr) {
    // Determine the new capacity
    size_t newCapacity = expand_capacity(vector->capacity, vector->size + count);
    // Update capacity
    int err = vector_reserve(vector, newCapacity);
    if (err) return err;
    // Resize
    void* dst = (char*)vector->data + vector->size * vector->element_size;
    memcpy(dst, arr, count * vector->element_size);
    vector->size += count;
    return 0;
}

void* vector_at(const Vector* vector, size_t idx) {
    if (idx >= vector->size) {
        fprintf(stderr, "Index out of range\n");
        return NULL;
    }
    return (char*)vector->data + idx * vector->element_size;
}

void* vector_front(Vector* vector) {
    if (!vector->size) {
        fprintf(stderr, "Vector is empty\n");
        return NULL;
    }
    return vector->data;
}

void* vector_back(Vector* vector) {
    if (!vector->size) {
        fprintf(stderr, "Vector is empty\n");
        return NULL;
    }
    return (char*)vector->data + (vector->size - 1) * vector->element_size;
}

size_t vector_remove(Vector* vector, size_t idx) {
    if (idx >= vector->size) return 0;
    char* dest = (char*)vector->data + idx * vector->element_size;
    char* src = dest + vector->element_size;
    size_t count = vector->size - idx - 1;
    memcpy(dest, src, count * vector->element_size);  // Safe because shifting left
    vector->size--;
    return 1;
}

size_t vector_clear(Vector* vector) {
    size_t size = vector->size;
    vector->size = 0;
    return size;
}

void vector_sort(Vector* vector, CompareFunc compare) {
    qsort(vector->data, vector->size, vector->element_size, compare);
}
