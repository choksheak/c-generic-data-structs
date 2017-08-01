// Implementation of a generic key and value hashmap.
// The code here strives to be minimal, so users can get minimal code bloat and raw performance.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "hashmap.h"

/*******************************************************************************************/

// Constructors.

struct hashmap *hashmap_createByteMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashByte, .cmpFunc = primitive_cmpByte };
    return hashmap_create(config);
}

struct hashmap *hashmap_createShortMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashShort, .cmpFunc = primitive_cmpShort };
    return hashmap_create(config);
}

struct hashmap *hashmap_createIntMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashInt, .cmpFunc = primitive_cmpInt };
    return hashmap_create(config);
}

struct hashmap *hashmap_createLongMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashLong, .cmpFunc = primitive_cmpLong };
    return hashmap_create(config);
}

struct hashmap *hashmap_createUByteMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashUByte, .cmpFunc = primitive_cmpUByte };
    return hashmap_create(config);
}

struct hashmap *hashmap_createUShortMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashUShort, .cmpFunc = primitive_cmpUShort };
    return hashmap_create(config);
}

struct hashmap *hashmap_createUIntMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashUInt, .cmpFunc = primitive_cmpUInt };
    return hashmap_create(config);
}

struct hashmap *hashmap_createULongMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashULong, .cmpFunc = primitive_cmpULong };
    return hashmap_create(config);
}

struct hashmap *hashmap_createFloatMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashFloat, .cmpFunc = primitive_cmpFloat };
    return hashmap_create(config);
}

struct hashmap *hashmap_createDoubleMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashDouble, .cmpFunc = primitive_cmpDouble };
    return hashmap_create(config);
}

struct hashmap *hashmap_createPointerMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashPointer, .cmpFunc = primitive_cmpPointer };
    return hashmap_create(config);
}

struct hashmap *hashmap_createCharMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashChar, .cmpFunc = primitive_cmpChar };
    return hashmap_create(config);
}

struct hashmap *hashmap_createWCharMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashWChar, .cmpFunc = primitive_cmpWChar };
    return hashmap_create(config);
}

struct hashmap *hashmap_createStringMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashString, .cmpFunc = primitive_cmpString };
    return hashmap_create(config);
}

struct hashmap *hashmap_createWStringMap() {
    struct hashmap_config config = { .hashFunc = primitive_hashWString, .cmpFunc = primitive_cmpWString };
    return hashmap_create(config);
}

struct hashmap *hashmap_create(struct hashmap_config config) {
    // Minimum capacity of 1 is to make sure we don't use calloc with a size of 0.
    // Otherwise we can allow for a minimum capacity of 0.
    if (config.initialCapacity < 1) {
        config.initialCapacity = HASHMAP_DEFAULT_INITIAL_CAPACITY;
    }

    if (config.loadFactorOverThousand < HASHMAP_MIN_LOAD_FACTOR_OVER_THOUSAND
            || config.loadFactorOverThousand > HASHMAP_MAX_LOAD_FACTOR_OVER_THOUSAND) {
        config.loadFactorOverThousand = HASHMAP_DEFAULT_LOAD_FACTOR_OVER_THOUSAND;
    }

    if (config.hashFunc == NULL) {
        printf("Error: hashmap: hashFunc cannot be NULL.\n");
        return NULL;
    }

    if (config.cmpFunc == NULL) {
        printf("Error: hashmap: cmpFunc cannot be NULL.\n");
        return NULL;
    }

    struct hashmap *map = (struct hashmap *) malloc(sizeof(struct hashmap));

    map->capacity = config.initialCapacity;
    map->loadFactorOverThousand = config.loadFactorOverThousand;
    map->hashFunc = config.hashFunc;
    map->cmpFunc = config.cmpFunc;

    map->size = 0;
    map->table = calloc(sizeof(struct hashmap_bucket *), config.initialCapacity);

    return map;
}

/*******************************************************************************************/

// Internal operations.

void private_hashmap_grow(struct hashmap *map) {
    uint32_t capacity = map->capacity;
    uint32_t newCapacity = (capacity <= 3) ? 7 : capacity * 2;
    struct hashmap_bucket **newTable = calloc(sizeof(struct hashmap_bucket *), newCapacity);

    for (uint32_t slot = 0, size = map->size; slot < capacity && size > 0; slot++) {
        struct hashmap_bucket *bucket = map->table[slot];
        while (bucket != NULL) {
            uint32_t newSlot = bucket->hashCode % newCapacity;
            struct hashmap_bucket *thisNode = bucket;
            bucket = bucket->next;

            thisNode->next = newTable[newSlot];
            newTable[newSlot] = thisNode;

            size--;
        }
    }

    free(map->table);
    map->table = newTable;
    map->capacity = newCapacity;
}

/*******************************************************************************************/

// Basic operations.

// Returns true if new key was added.
bool hashmap_put(struct hashmap *map, union primitive_value key, union primitive_value value) {

    uint32_t newLoadFactorOverThousand = ((map->size + 1) * 1000) / map->capacity;
    if (newLoadFactorOverThousand >= map->loadFactorOverThousand) {
        private_hashmap_grow(map);
    }

    uint32_t hashCode = map->hashFunc(key);
    uint32_t slot = hashCode % map->capacity;
    struct hashmap_bucket **addToNode = &(map->table[slot]);

    while (*addToNode != NULL) {
        if (map->cmpFunc((*addToNode)->key, key) == 0) {

            (*addToNode)->key = key;
            (*addToNode)->value = value;
            (*addToNode)->hashCode = hashCode;

            return false;
        }

        addToNode = &((*addToNode)->next);
    }

    struct hashmap_bucket *list = malloc(sizeof(struct hashmap_bucket));
    list->key = key;
    list->value = value;
    list->hashCode = hashCode;
    list->next = NULL;

    *addToNode = list;
    map->size++;
    return true;
}

// Returns NULL if key is not found.
union primitive_value *hashmap_get(struct hashmap *map, union primitive_value key) {
    uint32_t size = map->size;

    if (size == 0) {
        return NULL;
    }

    uint32_t hashCode = map->hashFunc(key);
    uint32_t slot = hashCode % map->capacity;
    struct hashmap_bucket *bucket = map->table[slot];

    while (bucket != NULL) {
        if (map->cmpFunc(bucket->key, key) == 0) {
            return &(bucket->value);
        }
        size--;
        if (size == 0) {
            break;
        }
        bucket = bucket->next;
    }

    return NULL;
}

union primitive_value hashmap_getOrDefault(struct hashmap *map, union primitive_value key, union primitive_value defaultValue) {
    union primitive_value *value = hashmap_get(map, key);
    return (value != NULL) ? *value : defaultValue;
}

bool hashmap_containsKey(struct hashmap *map, union primitive_value key) {
    return hashmap_get(map, key) != NULL;
}

// Returns true if key was removed.
bool hashmap_remove(struct hashmap *map, union primitive_value key) {
    struct iterator_return removedEntry;
    return hashmap_getAndRemove(map, key, &removedEntry);
}

bool hashmap_getAndRemove(struct hashmap *map, union primitive_value key, struct iterator_return *removedEntry) {
    if (map->size == 0) {
        return false;
    }

    uint32_t hashCode = map->hashFunc(key);
    uint32_t slot = hashCode % map->capacity;
    struct hashmap_bucket **removeFromNode = &(map->table[slot]);

    while (*removeFromNode != NULL) {
        if (map->cmpFunc((*removeFromNode)->key, key) == 0) {
            struct hashmap_bucket *removedNode = *removeFromNode;
            *removeFromNode = (*removeFromNode)->next;

            removedEntry->key = removedNode->key;
            removedEntry->value = removedNode->value;

            free(removedNode);

            map->size--;
            return true;
        }

        removeFromNode = &((*removeFromNode)->next);
    }

    return false;
}

void hashmap_clear(struct hashmap *map) {
    uint32_t size = map->size;

    if (size == 0) {
        return;
    }

    for (uint32_t slot = 0; slot < map->capacity; slot++) {
        struct hashmap_bucket *bucket = map->table[slot];
        map->table[slot] = NULL;

        while (bucket != NULL) {
            struct hashmap_bucket *next = bucket->next;

            free(bucket);
            bucket = next;

            size--;
            if (size == 0) {
                map->size = 0;
                return;
            }
        }
    }
}

/*******************************************************************************************/

// Iterators.

#define IteratorMap                 iteratorInternal1.pointerValue
#define IteratorCurrentSlot         iteratorInternal2.uintValue
#define IteratorNextBucket          iteratorInternal3.pointerValue

// Iterators do not allocate any memory and hence are very lightweight.
struct iterator hashmap_iterator(struct hashmap *map) {
    struct iterator iterator;

    iterator.nextFunc = hashmap_next;
    iterator.rewindFunc = hashmap_rewind;

    iterator.IteratorMap = map;
    hashmap_rewind(&iterator);

    return iterator;
}

// Returns true if a next key-value is available.
bool hashmap_next(struct iterator *iterator, struct iterator_return *returnValue) {
    struct hashmap *map = iterator->IteratorMap;
    uint32_t currentSlot = iterator->IteratorCurrentSlot;
    struct hashmap_bucket *nextBucket = iterator->IteratorNextBucket;

    while (nextBucket == NULL && currentSlot < map->capacity) {
        nextBucket = map->table[currentSlot++];
    }

    iterator->IteratorCurrentSlot = currentSlot;

    if (nextBucket == NULL) {
        iterator->IteratorNextBucket = NULL;

        // Always auto-rewind the hashmap for the next iteration.
        hashmap_rewind(iterator);
        return false;
    }

    returnValue->key = nextBucket->key;
    returnValue->value = nextBucket->value;
    iterator->IteratorNextBucket = nextBucket->next;
    return true;
}

void hashmap_rewind(struct iterator *iterator) {
    struct hashmap *map = iterator->IteratorMap;
    iterator->IteratorCurrentSlot = (map->size != 0) ? 1 : map->capacity;
    iterator->IteratorNextBucket = map->table[0];
}

#undef IteratorMap
#undef IteratorCurrentSlot
#undef IteratorNextBucket

/*******************************************************************************************/

// Destructor.

void hashmap_free(struct hashmap *map) {
    hashmap_clear(map);
    free(map->table);
    free(map);
}

/*******************************************************************************************/
