
#ifndef CCONTAINERKIT_TEST_CDEBUG_H
#define CCONTAINERKIT_TEST_CDEBUG_H
#include <CContainerKit/CDebug.h>

static void cdebug_test_1() {
    setMessageFormat("Type: %T,\t Text: %t");
    debug("Hello Debug!");
    info("This is an info!");
    throwError("This is an error!");
    warning("This is a warning!");
    critical("This is a critical!");
}

static void cdebug_test_2() {
    setMessageFormat("[%Y/%m/%d %H:%M:%S] %t");
    debug("Now (24 Hours)");
    setMessageFormat("[%Y/%m/%d %I:%M:%S %p] %t");
    debug("Now (12 Hours)");
}

static void CDebug_test() {
    printstr("=== CDebug Test ===", '\n');
    cdebug_test_1();
    cdebug_test_2();
}

#endif //CCONTAINERKIT_TEST_CDEBUG_H
