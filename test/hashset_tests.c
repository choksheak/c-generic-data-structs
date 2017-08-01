#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashset.h"

void print_hashset_int(struct iterator_return returnValue) {
    printf("{");
    printf("%" PRIi32, returnValue.value.intValue);
    printf("}");
}

void hashset_tests(void) {
    struct hashset *set = hashset_createIntSet();
    assert(set->size == 0);

    assert(hashset_put(set, primitive_getInt(3)) == true);
    assert(hashset_put(set, primitive_getInt(7)) == true);
    assert(hashset_put(set, primitive_getInt(8)) == true);
    assert(hashset_put(set, primitive_getInt(9)) == true);
    assert(hashset_put(set, primitive_getInt(3)) == false);
    assert(set->size == 4);

    assert(hashset_contains(set, primitive_getInt(10)) == false);
    assert(hashset_contains(set, primitive_getInt(11)) == false);
    assert(hashset_contains(set, primitive_getInt(9)) == true);
    assert(hashset_contains(set, primitive_getInt(7)) == true);

    assert(hashset_remove(set, primitive_getInt(8)) == true);
    assert(hashset_contains(set, primitive_getInt(8)) == false);
    assert(hashset_remove(set, primitive_getInt(8)) == false);

    hashset_clear(set);
    assert(set->size == 0);

    for (int32_t i = -100; i <= 100; i += 7) {
        hashset_put(set, primitive_getInt(i));
    }

    printf("Set each: ");
    struct iterator iter = hashset_iterator(set);
    iterator_each(&iter, print_hashset_int);
    puts("");

    hashset_free(set);
}
