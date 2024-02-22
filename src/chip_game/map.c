#include <chip_game/map.h>

size_t hash(char* key) {
    size_t hash = 0;
    while (*key) {
        hash = hash * 31 + *key++;
    }
    return hash % HASHMAP_SIZE;
}

void hashmap_init(HashMap* map) {
    for (size_t i = 0; i < HASHMAP_SIZE; i++) {
        vector_init(&map->buckets[i], sizeof(KeyValPair));
    }
}

void hashmap_free(HashMap* map) {
    for (size_t i = 0; i < HASHMAP_SIZE; i++) {
        vector_free(&map->buckets[i]);
    }
}

void hashmap_insert(HashMap* map, char* key, void* value) {
    unsigned int index = hash(key);
    KeyValPair pair;
    pair.key = strdup(key);
    pair.val = value;
    vector_push_back(&map->buckets[index], &pair);
}

void* hashmap_at(HashMap* map, char* key) {
    errno = 0;

    size_t index = hash(key);
    Vector* bucket = &map->buckets[index];
    size_t size = bucket->size;

    for (size_t i = 0; i < size; i++) {
        KeyValPair* pair = vector_at(bucket, i);
        if (strcmp(pair->key, key) == 0) {
            return pair->val;
        }
    }

    // Not found
    errno = EINVAL;
    return NULL;
}

int hashmap_remove(HashMap* map, char* key) {
    size_t index = hash(key);
    Vector* bucket = &map->buckets[index];
    for (size_t i = 0; i < bucket->size; i++) {
        KeyValPair* pair = vector_at(bucket, i);
        if (strcmp(pair->key, key) == 0) {
            free(pair->key);
            vector_remove(bucket, i); // Assuming vector_remove exists
            // No need to free pair->val
            return 1;
        }
    }
    return 0;
}

int hashmap_remove_and_free(HashMap* map, char* key) {
    size_t index = hash(key);
    Vector* bucket = &map->buckets[index];
    for (size_t i = 0; i < bucket->size; i++) {
        KeyValPair* pair = vector_at(bucket, i);
        if (strcmp(pair->key, key) == 0) {
            vector_remove(bucket, i); // Assuming vector_remove exists
            free(pair->key);
            free(pair->val);
            return 1;
        }
    }
    return 0;
}
