#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <chip_game/vector.h>

#define HASHMAP_SIZE 100

typedef struct {
    char* key;
    void* val;
} KeyValPair;

/**
 * Very simple hash map class that has a fixed size.
 */
typedef struct {
    Vector buckets[HASHMAP_SIZE]; // Array of Vectors for collision handling
} HashMap;

/**
 * Hash function used by the HashMap class.
 * @param key A string representing the key.
 * @return Hashed value.
 */
size_t hash(char* key);

/**
 * Constructor of HashMap.
 * @param map The hash map to initialize.
 */
void hashmap_init(HashMap* map);

/**
 * Destructor of HashMap.
 * @param map The hash map to destroy.
 */
void hashmap_free(HashMap* map);

void hashmap_insert(HashMap* map, char* key, void* value);

void* hashmap_at(HashMap* map, char* key);

int hashmap_remove(HashMap* map, char* key);

int hashmap_remove_and_free(HashMap* map, char* key);
