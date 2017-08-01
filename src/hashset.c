#include <stdbool.h>
#include <stdlib.h>

#include "hashset.h"
#include "hashmap.h"

/*******************************************************************************************/

// Constructors.

struct hashset *hashset_createByteSet() {
    struct hashset_config config = { .hashFunc = primitive_hashByte, .cmpFunc = primitive_cmpByte };
    return hashset_create(config);
}

struct hashset *hashset_createShortSet() {
    struct hashset_config config = { .hashFunc = primitive_hashShort, .cmpFunc = primitive_cmpShort };
    return hashset_create(config);
}

struct hashset *hashset_createIntSet() {
    struct hashset_config config = { .hashFunc = primitive_hashInt, .cmpFunc = primitive_cmpInt };
    return hashset_create(config);
}

struct hashset *hashset_createLongSet() {
    struct hashset_config config = { .hashFunc = primitive_hashLong, .cmpFunc = primitive_cmpLong };
    return hashset_create(config);
}

struct hashset *hashset_createUByteSet() {
    struct hashset_config config = { .hashFunc = primitive_hashUByte, .cmpFunc = primitive_cmpUByte };
    return hashset_create(config);
}

struct hashset *hashset_createUShortSet() {
    struct hashset_config config = { .hashFunc = primitive_hashUShort, .cmpFunc = primitive_cmpUShort };
    return hashset_create(config);
}

struct hashset *hashset_createUIntSet() {
    struct hashset_config config = { .hashFunc = primitive_hashUInt, .cmpFunc = primitive_cmpUInt };
    return hashset_create(config);
}

struct hashset *hashset_createULongSet() {
    struct hashset_config config = { .hashFunc = primitive_hashULong, .cmpFunc = primitive_cmpULong };
    return hashset_create(config);
}

struct hashset *hashset_createFloatSet() {
    struct hashset_config config = { .hashFunc = primitive_hashFloat, .cmpFunc = primitive_cmpFloat };
    return hashset_create(config);
}

struct hashset *hashset_createDoubleSet() {
    struct hashset_config config = { .hashFunc = primitive_hashDouble, .cmpFunc = primitive_cmpDouble };
    return hashset_create(config);
}

struct hashset *hashset_createPointerSet() {
    struct hashset_config config = { .hashFunc = primitive_hashPointer, .cmpFunc = primitive_cmpPointer };
    return hashset_create(config);
}

struct hashset *hashset_createCharSet() {
    struct hashset_config config = { .hashFunc = primitive_hashChar, .cmpFunc = primitive_cmpChar };
    return hashset_create(config);
}

struct hashset *hashset_createWCharSet() {
    struct hashset_config config = { .hashFunc = primitive_hashWChar, .cmpFunc = primitive_cmpWChar };
    return hashset_create(config);
}

struct hashset *hashset_createStringSet() {
    struct hashset_config config = { .hashFunc = primitive_hashString, .cmpFunc = primitive_cmpString };
    return hashset_create(config);
}

struct hashset *hashset_createWStringSet() {
    struct hashset_config config = { .hashFunc = primitive_hashWString, .cmpFunc = primitive_cmpWString };
    return hashset_create(config);
}

struct hashset *hashset_create(struct hashset_config config) {
    struct hashset *set = (struct hashset *) malloc(sizeof(struct hashset));
    set->size = 0;

    struct hashmap_config map_config = {
            .initialCapacity = config.initialCapacity,
            .loadFactorOverThousand = config.loadFactorOverThousand,
            .hashFunc = config.hashFunc,
            .cmpFunc = config.cmpFunc
    };

    set->map = hashmap_create(map_config);
    return set;
}

/*******************************************************************************************/

// Basic operations.

bool hashset_put(struct hashset *set, union primitive_value value) {
    // Store both key and value as value for use in iterator.
    if (hashmap_put(set->map, value, value)) {
        set->size = set->map->size;
        return true;
    }
    return false;
}

bool hashset_contains(struct hashset *set, union primitive_value value) {
    return hashmap_containsKey(set->map, value);
}

bool hashset_remove(struct hashset *set, union primitive_value value) {
    if (hashmap_remove(set->map, value)) {
        set->size = set->map->size;
        return true;
    }
    return false;
}

void hashset_clear(struct hashset *set) {
    hashmap_clear(set->map);
    set->size = 0;
}

/*******************************************************************************************/

// Iterators.

struct iterator hashset_iterator(struct hashset *set) {
    return hashmap_iterator(set->map);
}

bool hashset_next(struct iterator *iterator, struct iterator_return *returnValue) {
    return hashmap_next(iterator, returnValue);
}

void hashset_rewind(struct iterator *iterator) {
    hashmap_rewind(iterator);
}

/*******************************************************************************************/

// Destructor.

void hashset_free(struct hashset *set) {
    hashmap_free(set->map);
    free(set);
}

/*******************************************************************************************/
