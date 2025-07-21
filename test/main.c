
#include "unit_tests/Test_CArray.h"
#include "unit_tests/Test_CVector.h"
#include "unit_tests/Test_CStack.h"
#include  "unit_tests/Test_CDeque.h"
#include "unit_tests/Test_CString.h"
#include "unit_tests/Test_CDebug.h"
#include <string.h>

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s [TEST_CASE]\n", argv[0]);
        printf("Avaliable Test case: \n");
        printf("- array\n"
               "- string\n"
               "- vector\n"
               "- stack\n"
               "- deque\n"
               "- debug"
               "e.g: To test [CArray], just type: %s array\n", argv[0]);
        return 1;
    }
    if (!strcmp(argv[1], "array")) {
        CArray_test();
    } else if (!strcmp(argv[1], "string")) {
        CString_test();
    } else if (!strcmp(argv[1], "vector")) {
        CVector_test();
    } else if (!strcmp(argv[1], "stack")) {
        CStack_test();
    } else if (!strcmp(argv[1], "deque")) {
        CDeque_test();
    } else if (!strcmp(argv[1], "debug")) {
        CDebug_test();
    } else {
        printf("Error: Unknown test case name: %s!\n", argv[1]);
    }
    return 0;
}
