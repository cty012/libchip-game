#include <chip_game/map.h>

size_t hash(const char* key) {
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
    map->size = 0;
}

void hashmap_free(HashMap* map, bool free_val) {
    for (size_t i = 0; i < HASHMAP_SIZE; i++) {
        Vector* bucket = &map->buckets[i];
        size_t bucket_size = vector_size(bucket);
        for (size_t j = 0; j < bucket_size; j++) {
            KeyValPair* pair = vector_at(bucket, j);
            free(pair->key);
            if (free_val) free(pair->val);
        }
        vector_free(bucket);
    }
}

size_t hashmap_size(HashMap* map) {
    return map->size;
}

size_t hashmap_insert(HashMap* map, char* key, void* value, bool free_val) {
    size_t index = hash(key);
    Vector* bucket = &map->buckets[index];
    size_t bucket_size = vector_size(bucket);

    for (size_t i = 0; i < bucket_size; i++) {
        KeyValPair* pair = vector_at(bucket, i);
        if (strcmp(pair->key, key) == 0) {
            if (free_val) free(pair->val);
            pair->val = value;
            return 0;
        }
    }

    // If not exist
    KeyValPair pair;
    pair.key = strdup(key);
    pair.val = value;
    vector_push_back(&map->buckets[index], &pair);
    map->size++;
    return 1;
}

void* hashmap_at(HashMap* map, const char* key) {
    errno = 0;

    size_t index = hash(key);
    Vector* bucket = &map->buckets[index];
    size_t bucket_size = vector_size(bucket);

    for (size_t i = 0; i < bucket_size; i++) {
        KeyValPair* pair = vector_at(bucket, i);
        if (strcmp(pair->key, key) == 0) {
            return pair->val;
        }
    }

    // Not found
    errno = EINVAL;
    return NULL;
}

size_t hashmap_remove(HashMap* map, const char* key, bool free_val) {
    size_t index = hash(key);
    Vector* bucket = &map->buckets[index];
    size_t bucket_size = vector_size(bucket);
    for (size_t i = 0; i < bucket_size; i++) {
        KeyValPair* pair = vector_at(bucket, i);
        if (strcmp(pair->key, key) == 0) {
            free(pair->key);
            if (free_val) free(pair->val);
            vector_remove(bucket, i);
            map->size--;
            return 1;
        }
    }
    return 0;
}

size_t hashmap_clear(HashMap* map, bool free_val) {
    size_t size = map->size;
    for (size_t i = 0; i < HASHMAP_SIZE; i++) {
        Vector* bucket = &map->buckets[i];
        size_t bucket_size = vector_size(bucket);
        for (size_t j = 0; j < bucket_size; j++) {
            KeyValPair* pair = vector_at(bucket, j);
            free(pair->key);
            if (free_val) free(pair->val);
        }
        vector_clear(&map->buckets[i]);
    }
    map->size = 0;
    return size;
}

int hashmap_keys(HashMap* map, Vector* vector) {
    if (vector->element_size != sizeof(char*)) return 1;
    vector_clear(vector);
    vector_reserve(vector, map->size);
    for (size_t i = 0; i < HASHMAP_SIZE; i++) {
        Vector* bucket = &map->buckets[i];
        size_t bucket_size = vector_size(bucket);

        for (size_t j = 0; j < bucket_size; j++) {
            KeyValPair* pair = (KeyValPair*)vector_at(bucket, j);
            vector_push_back(vector, &pair->key);
        }
    }
    return 0;
}

int hashmap_iterate(HashMap* map, Vector* vector) {
    if (vector->element_size != sizeof(KeyValPair*)) return 1;
    vector_clear(vector);
    vector_reserve(vector, map->size);
    for (size_t i = 0; i < HASHMAP_SIZE; i++) {
        Vector* bucket = &map->buckets[i];
        size_t bucket_size = vector_size(bucket);

        for (size_t j = 0; j < bucket_size; j++) {
            KeyValPair* pair = (KeyValPair*)vector_at(bucket, j);
            vector_push_back(vector, &pair);
        }
    }
    return 0;
}
