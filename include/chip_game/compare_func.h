/**
 * Defines a total order on the given elements.
 *  - If element one should appear before element two, return a negative number.
 *  - If element two should appear after element two, return a positive number.
 *  - Otherwise they must be equal. Return 0.
 *
 * Note that defining a partial order instead of a total order is undefined behavior.
 */
typedef int (*CompareFunc)(const void*, const void*);

// TODO: doc
int compare_int_inc(const void* a, const void* b);
int compare_int_dec(const void* a, const void* b);
