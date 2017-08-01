#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"
#include "strbuf.h"

void print_hashmap_int(struct iterator_return returnValue) {
    printf("{");
    printf("%" PRIi32, returnValue.key.intValue);
    printf("=");
    printf("%" PRIi32, returnValue.value.intValue);
    printf("}");
}

void hashmap_tests(void) {
    struct hashmap *map = hashmap_createIntMap();

    char *s1 = "hi";
    char *s2 = "ha";
    char *s3 = "ho";

    hashmap_put(map, primitive_getInt(1), primitive_getString(s1));
    hashmap_put(map, primitive_getInt(2), primitive_getString(s2));
    hashmap_remove(map, primitive_getInt(3));
    hashmap_put(map, primitive_getInt(4), primitive_getString(s3));
    hashmap_put(map, primitive_getInt(4), primitive_getString(s1));
    hashmap_put(map, primitive_getInt(5), primitive_getString(s2));

    union primitive_value *value = hashmap_get(map, primitive_getString(s1));
    assert(value == NULL);

    value = hashmap_get(map, primitive_getInt(4));
    assert(value->stringValue == s1);

    hashmap_remove(map, primitive_getInt(2));

    value = hashmap_get(map, primitive_getInt(2));
    assert(value == NULL);

    union primitive_value val = hashmap_getOrDefault(map, primitive_getInt(2), primitive_getString(""));
    assert(strlen(val.stringValue) == 0);

    value = hashmap_get(map, primitive_getInt(1));
    assert(value != NULL);

    hashmap_remove(map, primitive_getInt(1));
    assert(hashmap_get(map, primitive_getInt(1)) == NULL);

    hashmap_clear(map);

    for (int i = 0; i < 1000; i++) {
        assert(map->size == i);
        hashmap_put(map, primitive_getInt(i), primitive_getString("A"));
        assert(hashmap_containsKey(map, primitive_getInt(i)) == true);
    }

    for (int i = 0; i < 1000; i += 2) {
        int size = map->size;
        hashmap_remove(map, primitive_getInt(i));
        assert(hashmap_containsKey(map, primitive_getInt(i)) == false);
        assert(map->size == size - 1);
    }

    hashmap_free(map);

    map = hashmap_createIntMap();

    struct iterator iter1 = hashmap_iterator(map);
    struct iterator_return returnValue;
    assert(iter1.nextFunc(&iter1, &returnValue) == false);

    printf("Capacity: ");
    for (int i = 0; i < 10; i++) {
        hashmap_put(map, primitive_getInt(i * 23), primitive_getInt(i * 12));
        printf("{%u=%u} ", map->size, map->capacity);
    }
    puts("");

    printf("Map each: ");
    struct iterator iter = hashmap_iterator(map);
    iterator_each(&iter, print_hashmap_int);
    puts("");

    hashmap_clear(map);
    assert(map->size == 0);

    hashmap_free(map);

    map = hashmap_createStringMap();

    hashmap_put(map, primitive_getString(string_dup("k1")), primitive_getString(string_dup("v1")));
    hashmap_put(map, primitive_getString(string_dup("k2")), primitive_getString(string_dup("v2")));

    assert(hashmap_getAndRemove(map, primitive_getString("k1"), &returnValue) == true);
    free(returnValue.key.stringValue);
    free(returnValue.value.stringValue);

    assert(hashmap_getAndRemove(map, primitive_getString("k2"), &returnValue) == true);
    free(returnValue.key.stringValue);
    free(returnValue.value.stringValue);

    hashmap_free(map);
}
