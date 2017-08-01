#include "iterator.h"

void iterator_each(struct iterator *iterator, void (*func)(struct iterator_return)) {
    struct iterator_return returnValue;
    bool (*nextFunc)(struct iterator *, struct iterator_return *) = iterator->nextFunc;

    while (nextFunc(iterator, &returnValue)) {
        func(returnValue);
    }
}
