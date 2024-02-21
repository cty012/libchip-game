#pragma once

#include <stdbool.h>
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

/**
 * Checks whether the vector is empty.
 * @param vector The target vector.
 * @return Whether the vector has size 0.
 */
bool vector_empty(Vector* vector);

/**
 * Reserve capacity in the vector. New capacity will be at least as large as the current size of the vector.
 * @param vector The target vector.
 * @param capacity The capacity to reserve (will downsize).
 * @return Error code:
 *  - 0: Success.
 *  - 1: Failed to reallocate memory.
 */
int vector_reserve(Vector* vector, size_t capacity);

/**
 * Resize the vector.
 * @param vector The target vector.
 * @param size The new size of the vector. If downsize, will cut from the tail.
 * @param prototype If the size increases, will use this prototype to fill the blanks.
 * @return Error code:
 *  - 0: Success.
 *  - 1: Failed to expand capacity.
 */
int vector_resize(Vector* vector, size_t size, void* prototype);

/**
 * Push an element to the back of the vector.
 * @param vector The target vector.
 * @param element The pointer to the element to push into the vector.
 * @return Error code:
 *  - 0: Success.
 *  - 1: Failed to expand capacity.
 */
int vector_push_back(Vector* vector, void* element);

/**
 * Access an element in the vector. For invalid indices, NULL is returned.
 * @param vector The target vector.
 * @param idx Index of the element to access.
 * @return The pointer to the element stored in the vector with the given index.
 */
void* vector_at(Vector* vector, size_t idx);

/**
 * Access the first element in the vector. NULL is returned for empty vectors.
 * @param vector The target vector.
 * @return The pointer to the first element in the vector.
 */
void* vector_front(Vector* vector);

/**
 * Access the last element in the vector. NULL is returned for empty vectors.
 * @param vector The target vector.
 * @return The pointer to the last element in the vector.
 */
void* vector_back(Vector* vector);

/**
 * Sort the vector according to the compare function.
 * @param vector The target vector.
 * @param compare The compare function that defines the total order of vector elements.
 */
void vector_sort(Vector* vector, CompareFunc compare);
