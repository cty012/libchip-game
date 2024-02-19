#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct {
    void* data;
    size_t element_size;
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector* vector, size_t element_size) {
    vector->element_size = element_size;
    vector->size = 0;
    vector->capacity = 4;
    vector->data = malloc(vector->capacity * element_size);
}

void vector_push_back(Vector* vector, void* element) {
    if (vector->size == vector->capacity) {
        vector->capacity = vector->capacity * 2;
        vector->data = realloc(vector->data, vector->capacity * vector->element_size);
    }
    memcpy((char*)vector->data + vector->size * vector->element_size, element, vector->element_size);
    vector->size++;
}

void vector_free(Vector* vector) {
    free(vector->data);
    vector->data = NULL;
    vector->size = vector->capacity = 0;
}
