
#ifndef CCONTAINERKIT_TEST_CDEBUG_H
#define CCONTAINERKIT_TEST_CDEBUG_H
#include <CContainerKit/CDebug.h>

// Test 1: Output different levels of information.
static void cdebug_test_1() {
    printf("[Test 1]\n");
    setMessageFormat("Type: %T,\t Text: %t");
    debug("Hello Debug!");
    info("This is an info!");
    throwError("This is an error!");
    warning("This is a warning!");
    critical("This is a critical!");
}

// Test 2: Output different datetime formats
static void cdebug_test_2() {
    printf("\n[Test 2]\n");
    setMessageFormat("[%Y/%m/%d %H:%M:%S]");
    debug("");
    setMessageFormat("[%Y/%m/%d %I:%M:%S %P]");
    debug("");
    setMessageFormat("[%B %A %d %I:%M:%S %P %Y]");
    debug("");
    setMessageFormat("[%f]");
    debug("");
}

static void CDebug_test() {
    printstr("=== CDebug Test ===", '\n');
    cdebug_test_1();
    cdebug_test_2();
}

#endif //CCONTAINERKIT_TEST_CDEBUG_H
