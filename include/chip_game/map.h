#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <chip_game/vector.h>

#define HASHMAP_SIZE 100

typedef struct {
    char* key;  // owned by HashMap
    void* val;  // owned by user (only freed in hashmap_remove_and_free)
} KeyValPair;

/**
 * Very simple hash map class that has a fixed size.
 */
typedef struct {
    Vector buckets[HASHMAP_SIZE]; // Array of Vectors for collision handling
    size_t size;
} HashMap;

/**
 * Hash function used by the HashMap class.
 * @param key A string representing the key.
 * @return Hashed value.
 */
size_t hash(const char* key);

/**
 * Constructor of HashMap.
 * @param map The hash map to initialize.
 */
void hashmap_init(HashMap* map);

/**
 * Destructor of HashMap.
 * @param map The hash map to destroy.
 * @param free_val Whether to free the values stored in key-value pairs.
 */
void hashmap_free(HashMap* map, bool free_val);

/**
 * @param map The target hash map.
 * @return The size of the hash map.
 */
size_t hashmap_size(HashMap* map);

/**
 * Insert a key-value pair into the hash map.
 * @param map The target hash map to insert into.
 * @param key The key.
 * @param value The value. Will overwrite original value if key exists.
 * @param free_val If need to overwrite, whether to free the values stored in key-value pairs.
 * @return The number of elements inserted (0 if overwrite).
 */
size_t hashmap_insert(HashMap* map, char* key, void* value, bool free_val);

void* hashmap_at(HashMap* map, const char* key);

size_t hashmap_remove(HashMap* map, const char* key, bool free_val);

size_t hashmap_clear(HashMap* map, bool free_val);

/**
 * Fills the vector with keys.
 * @param map The hash map to iterate.
 * @param vector [Vector<char*>] The vector to fill. Assumed to be initialized.
 * @return Error code. 0: Success; 1: invalid argument;
 */
int hashmap_keys(HashMap* map, Vector* vector);

/**
 * Fills the vector with pointers to the key-value pairs.
 * @param map The hash map to iterate.
 * @param vector [Vector<KeyValPair*>] The vector to fill. Assumed to be initialized.
 * @return Error code. 0: Success; 1: invalid argument;
 */
int hashmap_iterate(HashMap* map, Vector* vector);
