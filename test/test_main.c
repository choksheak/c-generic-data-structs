#include <stdio.h>

// Rather than adding header files, we just list out test methods.
// There is only one test method per test file, like "void <filename>(void)".
extern void hashmap_tests(void);
extern void arraylist_tests(void);
extern void strbuf_tests(void);
extern void hashset_tests(void);

void run_test(char *test_name, void (*test_func)(void)) {
    printf("Start %s\n", test_name);
    test_func();
    printf("Done %s\n\n", test_name);
}

int main(void) {
    run_test("hashmap_tests", hashmap_tests);
    run_test("arraylist_tests", arraylist_tests);
    run_test("strbuf_tests", strbuf_tests);
    run_test("hashset_tests", hashset_tests);
}
