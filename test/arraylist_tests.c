#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "arraylist.h"

void print_arraylist_int(struct iterator_return returnValue) {
    printf("(%" PRIi32 ")", returnValue.value.intValue);
}

void arraylist_tests(void) {
    struct arraylist *list = arraylist_create();

    arraylist_add(list, primitive_getInt(4));
    arraylist_add(list, primitive_getInt(5));

    assert(arraylist_remove(list, 0).intValue == 4);

    arraylist_set(list, 0, primitive_getInt(10));
    assert(arraylist_get(list, 0).intValue == 10);

    for (uint32_t i = 1; i < 1000; i++) {
        assert(list->size == i);
        arraylist_add(list, primitive_getInt(i * 3));
    }

    uint32_t size = list->size;
    arraylist_remove(list, 5);
    assert(list->size == size - 1);

    while (list->size > 10) {
        arraylist_remove(list, 1);
    }
    assert(list->size == 10);

    printf("each: ");
    struct iterator iterator = arraylist_iterator(list);
    iterator_each(&iterator, print_arraylist_int);
    puts("");

    arraylist_clear(list);
    assert(list->size == 0);

    for (uint32_t i = 1; i <= 10; i++) {
        arraylist_add(list, primitive_getInt(i));
    }

    assert(list->size == 10);

    arraylist_removeRange(list, 8, 10);
    assert(list->size == 8);
    assert(arraylist_get(list, 7).intValue == 8);

    arraylist_removeRange(list, 0, 2);
    assert(list->size == 6);
    assert(arraylist_get(list, 0).intValue == 3);

    arraylist_removeRange(list, 5, 5);
    assert(list->size == 6);

    arraylist_removeRange(list, 5, 6);
    assert(list->size == 5);

    arraylist_removeRange(list, 0, 0);
    assert(list->size == 5);

    arraylist_removeRange(list, 0, 1);
    assert(list->size == 4);

    arraylist_free(list);
}
