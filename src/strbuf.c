#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "strbuf.h"

/*******************************************************************************************/

// Utils.

char *string_dup(const char *s) {
    size_t len = strlen(s) + 1;
    char *t = malloc(len);
    if (t != NULL) {
        memcpy(t, s, len);
    }
    return t;
}

/*******************************************************************************************/

// Constructors.

struct strbuf *strbuf_create(void) {
    return strbuf_create1(0);
}

struct strbuf *strbuf_create1(uint32_t initialCapacity) {
    if (initialCapacity == 0) {
        initialCapacity = STRBUF_DEFAULT_INITIAL_CAPACITY;
    }

    struct strbuf *buf = (struct strbuf *) malloc(sizeof(struct strbuf));
    buf->size = 0;
    buf->capacity = initialCapacity;
    buf->string = (char *) malloc(sizeof(char) * (initialCapacity + 1));
    buf->string[0] = '\0';
    return buf;
}

/*******************************************************************************************/

// Basic operations.

void strbuf_grow(struct strbuf *buf, uint32_t newCapacity) {
    buf->string = realloc(buf->string, sizeof(char) * (newCapacity + 1));
    buf->capacity = newCapacity;
}

void strbuf_puts(struct strbuf *buf, char *s) {
    if (s != NULL) {
        uint32_t len = strlen(s);
        if (len + buf->size > buf->capacity) {
            strbuf_grow(buf, (len + buf->size) * 2);
        }

        uint32_t size = buf->size;
        for (uint32_t i = 0; i < len; i++) {
            buf->string[size + i] = s[i];
        }

        size += len;
        buf->string[size] = '\0';
        buf->size = size;
    }
}

void strbuf_putc(struct strbuf *buf, char c) {
    if (buf->size == buf->capacity) {
        strbuf_grow(buf, buf->capacity * 2);
    }

    buf->string[buf->size++] = c;
    buf->string[buf->size] = '\0';
}

bool private_strbuf_checkBounds(struct strbuf *buf, uint32_t index) {
    if (index >= buf->size) {
        printf("Error: strbuf: Index %" PRIu32 " out of bounds. String length is %" PRIu32 ".\n", index, buf->size);
        return false;
    }
    return true;
}

char strbuf_get(struct strbuf *buf, uint32_t index) {
    return private_strbuf_checkBounds(buf, index) ? buf->string[index] : '\0';
}

void strbuf_set(struct strbuf *buf, uint32_t index, char c) {
    if (private_strbuf_checkBounds(buf, index)) {
        buf->string[index] = c;
    }
}

void strbuf_clear(struct strbuf *buf) {
    buf->size = 0;
    buf->string[0] = '\0';
}

/*******************************************************************************************/

// Destructor.

void strbuf_free(struct strbuf *buf) {
    free(buf->string);
    free(buf);
}

/*******************************************************************************************/
