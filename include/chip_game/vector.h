#pragma once

#include <stdlib.h>

/**
 * Compares two elements. If the first is less than the second, return a negative number. If the first is greater than
 * the second, return a positive number. Otherwise 0 is returned.
 */
typedef int (*CompareFunc)(const void*, const void*);

typedef struct {
    void* data;
    size_t element_size;
    size_t size;
    size_t capacity;
} Vector;

/**
 * Constructor of Vector.
 * @param vector The vector to initialize.
 * @param element_size
 */
void vector_init(Vector* vector, size_t element_size);

/**
 * Destructor of Vector.
 * @param vector The vector to destroy.
 */
void vector_free(Vector* vector);

/**
 * Push an element to the back of the vector.
 * @param vector The target vector.
 * @param element The pointer to the element to push into the vector.
 */
void vector_push_back(Vector* vector, void* element);

/**
 * Access an element in the vector.
 * @param vector The target vector.
 * @param idx Index of the element to access.
 * @return The pointer to the element stored in the vector.
 */
void* vector_at(Vector* vector, size_t idx);

/**
 * Sort the vector from small to large.
 * @param vector
 * @param compare A compare function
 */
void vector_sort(Vector* vector, CompareFunc compare);
