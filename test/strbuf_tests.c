#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "strbuf.h"

void strbuf_tests(void) {
    struct strbuf *buf = strbuf_create();
    assert(buf->size == 0);

    strbuf_puts(buf, "Hello");
    strbuf_putc(buf, ' ');
    strbuf_puts(buf, "World");
    printf("strbuf1: %s\n", buf->string);

    assert(strbuf_get(buf, 4) == 'o');
    strbuf_set(buf, 4, 'a');
    assert(strbuf_get(buf, 4) == 'a');

    strbuf_clear(buf);
    assert(buf->size == 0);

    for (uint32_t i = 0; i < 100; i++) {
        strbuf_putc(buf, 'a' + i % 26);
        if (i % 8 == 0) strbuf_putc(buf, ' ');
    }

    printf("strbuf2: %s\n", buf->string);

    strbuf_free(buf);
}
