#pragma once

#include <stdlib.h>
#include <chip_game/compare_func.h>

/**
 * Generic vector class.
 */
typedef struct {
    void* data;
    size_t element_size;
    size_t size;
    size_t capacity;
} Vector;

/**
 * Constructor of Vector.
 * @param vector The vector to initialize.
 * @param element_size Size of each element.
 */
void vector_init(Vector* vector, size_t element_size);

/**
 * Destructor of Vector.
 * @param vector The vector to destroy.
 */
void vector_free(Vector* vector);

// TODO
void vector_reserve(Vector* vector, size_t capacity);

// TODO
void vector_resize(Vector* vector, size_t size);

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
 * Sort the vector according to the compare function.
 * @param vector The target vector.
 * @param compare The compare function that defines the total order of vector elements.
 */
void vector_sort(Vector* vector, CompareFunc compare);
