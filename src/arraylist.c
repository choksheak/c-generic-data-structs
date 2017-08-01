// Implementation of a generic value arraylist.
// The main functionality is the auto-extending of the array.

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arraylist.h"

/*******************************************************************************************/

// Constructors.

struct arraylist *arraylist_create(void) {
    return arraylist_create1(ARRAYLIST_DEFAULT_INITIAL_CAPACITY);
}

struct arraylist *arraylist_create1(uint32_t initialCapacity) {
    if (initialCapacity == 0) {
        initialCapacity = ARRAYLIST_DEFAULT_INITIAL_CAPACITY;
    }

    struct arraylist *list = (struct arraylist *) malloc(sizeof(struct arraylist));
    list->size = 0;
    list->capacity = initialCapacity;
    list->values = (union primitive_value *) calloc(initialCapacity, sizeof(union primitive_value));

    return list;
}

/*******************************************************************************************/

// Basic operations.

bool private_arraylist_checkBounds(uint32_t listSize, uint32_t index) {
    if (index >= listSize) {
        printf("Error: arraylist: Index %" PRIu32 " out of bounds. List size is %" PRIu32 ".\n", index, listSize);
        return false;
    }
    return true;
}

void private_arraylist_grow(struct arraylist *list) {
    list->capacity *= 2;
    list->values = (union primitive_value *) realloc(list->values, list->capacity * sizeof(union primitive_value));
}

void arraylist_add(struct arraylist *list, union primitive_value value) {
    if (list->size == list->capacity) {
        private_arraylist_grow(list);
    }

    list->values[list->size++] = value;
}

union primitive_value arraylist_get(struct arraylist *list, uint32_t index) {
    if (private_arraylist_checkBounds(list->size, index) == false) {
        return primitive_null;
    }

    return list->values[index];
}

void arraylist_set(struct arraylist *list, uint32_t index, union primitive_value value) {
    if (private_arraylist_checkBounds(list->size, index) == false) {
        return;
    }

    list->values[index] = value;
}

union primitive_value arraylist_remove(struct arraylist *list, uint32_t index) {
    if (private_arraylist_checkBounds(list->size, index) == false) {
        return primitive_null;
    }

    union primitive_value removedValue = list->values[index];

    list->size--;
    for (uint32_t i = index; i < list->size; i++) {
        list->values[i] = list->values[i + 1];
    }

    list->values[list->size] = primitive_null;

    return removedValue;
}

void arraylist_clear(struct arraylist *list) {
    memset(list->values, 0, list->size * sizeof(union primitive_value));
    list->size = 0;
}

/*******************************************************************************************/

// More operations.

void arraylist_removeRange(struct arraylist *list, uint32_t fromIndexInclusive, uint32_t toIndexExclusive) {
    if (private_arraylist_checkBounds(list->size, fromIndexInclusive) == false) {
        return;
    }

    if (private_arraylist_checkBounds(list->size, toIndexExclusive - 1) == false) {
        return;
    }

    if (toIndexExclusive == list->size) {
        list->size = fromIndexInclusive;
        memset(&(list->values[fromIndexInclusive]), 0, (toIndexExclusive - fromIndexInclusive) * sizeof(union primitive_value));
        return;
    }

    uint32_t len = toIndexExclusive - fromIndexInclusive;
    for (uint32_t i = 0; i < len; i++) {
        list->values[fromIndexInclusive + i] = list->values[toIndexExclusive + i];
    }

    memset(&(list->values[toIndexExclusive]), 0, (list->size - toIndexExclusive) * sizeof(union primitive_value));
    list->size -= len;
}

/*******************************************************************************************/

// Iterators.

#define IteratorList                iteratorInternal1.pointerValue
#define IteratorNextIndex           iteratorInternal2.uintValue

struct iterator arraylist_iterator(struct arraylist *list) {
    struct iterator iterator;

    iterator.nextFunc = arraylist_next;
    iterator.rewindFunc = arraylist_rewind;

    iterator.IteratorList = list;
    iterator.IteratorNextIndex = 0;

    return iterator;
}

bool arraylist_next(struct iterator *iterator, struct iterator_return *returnValue) {
    struct arraylist *list = (struct arraylist *) iterator->IteratorList;

    if (iterator->IteratorNextIndex >= list->size) {
        // Always auto-rewind the hashmap for the next iteration.
        arraylist_rewind(iterator);

        return false;
    }

    returnValue->value = list->values[iterator->IteratorNextIndex++];
    return true;
}

void arraylist_rewind(struct iterator *iterator) {
    iterator->IteratorNextIndex = 0;
}

#undef IteratorList
#undef IteratorNextIndex

/*******************************************************************************************/

// Destructor.

void arraylist_free(struct arraylist *list) {
    free(list->values);
    free(list);
}

/*******************************************************************************************/
