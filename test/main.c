
#include "unit_tests/carray_test.h"
#include "unit_tests/cvector_test.h"
#include <string.h>

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s [TEST_CASE]\n", argv[0]);
        printf("Avaliable Test case: \n");
        printf("- arrayList\n"
               "- string\n"
               "- variant\n"
               "- vectorList\n"
               "e.g: To test [CArray], just type: %s arrayList\n", argv[0]);
        return 1;
    }
    if (!strcmp(argv[1], "arrayList")) {
        carray_test();
    } else if (!strcmp(argv[1], "vector")) {
        cvector_test();
    } else {
        printf("Error: Unknown test case name: %s!\n", argv[1]);
    }
    return 0;
}
