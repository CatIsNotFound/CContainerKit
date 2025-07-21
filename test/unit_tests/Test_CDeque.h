
#ifndef CCONTAINERKIT_TEST_CDEQUE_H
#define CCONTAINERKIT_TEST_CDEQUE_H

#include "CContainerKit/CDeque.h"

// Test 1: CDeque initialization test.
static void cdeq_test1(void) {
    printf("[Test 1]\n");
    double d = 123.45;
    const char s[] = "CDeque";
    CDeque deque1 = dequeInit(3),
           deque2 = dequeInitType(TYPE_INT32, 5),
           deque3 = dequeList(4, varULongLong(1234567890), varChar('A'), varDouble(d), varString(s));

    CVariant var;
    printf("deque1: ");
    forEachDeqElements(var, deque1) {
        printVarData(var);
        printf(" (%s) ", varTypeName(var));
    }
    printf("\nLength: %d, Capacity: %d", deqLength(deque1), deqCapacity(deque1));
    printf("\ndeque2: ");
    forEachDeqElements(var, deque2) {
        printVarData(var);
        printf(" (%s) ", varTypeName(var));
    }
    printf("\nLength: %d, Capacity: %d", deqLength(deque2), deqCapacity(deque2));
    printf("\ndeque3: ");
    forEachDeqElements(var, deque3) {
        printVarData(var);
        printf(" (%s) ", varTypeName(var));
    }
    printf("\nLength: %d, Capacity: %d", deqLength(deque3), deqCapacity(deque3));
    printLine();
    destroyDeque(deque1);
    destroyDeque(deque2);
    deleteDeque(deque3);
}

// Test 2: Conversion between CDeque and CVector.
static void cdeq_test2(void) {
    printf("\n[Test 2]\n");
    CDeque deque1 = dequeList(3, varChar('A'), varInt(8888), varString("Deque To Vector"));
    CVector vector1 = deqToVector(deque1, true, NULL);
    CVariant var;
    printf("deque to vector: ");
    forEachVecElements(var, vector1) {
        printVarData(var);
        printf("(%s) | ", varTypeName(var));
    }
    printLine();
    float f = 123.45f;
    CVector vector2 = vectorList(3, varInt(50), varFloat(f), varString("Vector To Deque"));
    CDeque deque2 = vecToDeque(vector2, true, NULL);
    printf("vector to deque: ");
    forEachDeqElements(var, deque2) {
        printVarData(var);
        printf("(%s) | ", varTypeName(var));
    }
    printLine();
    deleteVector(vector1);
    deleteDeque(deque2);
}

// Test 3: Resize, Addition and deletion of elements.
static void cdeq_test3(void) {
    printf("\n[Test 3]\n");
    CDeque deque1 = dequeInit(5);
    printf("[Deque 1] length: %d, capacity: %d\n", deqLength(deque1), deqCapacity(deque1));
    resizeDeque(deque1, 30);
    printf("[Deque 1 Resized] length: %d, capacity: %d\n", deqLength(deque1), deqCapacity(deque1));
    deqClear(deque1);
    printf("[Deque 1 Clear] length: %d, capacity: %d\n", deqLength(deque1), deqCapacity(deque1));
    printLine();
    float f = 1.234f;
    CDeque deque2 = dequeList(5, varChar('#'), varUChar('P'), varShort(1024), varFloat(f), varString("qwerty"));
    CArray arr = arrayList(5, varInt(30), varChar('A'), varFloat(f), varEnum(TYPE_STRUCT, "dataType"),
                           varString("Test String"));
    deqPop(deque2);
    Time time = {10, 20, 30};
    deqPush(deque2, varStruct(time, "Time"));
    deqPushFromArray(deque2, arr);
    printf("[Deque 2] length: %d, capacity: %d\n",
           deqLength(deque2), deqCapacity(deque2));
    CVariant var;
    forEachDeqElements(var, deque2) {
        printVarData(var);
        printf(" (%s) | ", varTypeName(var));
    }
    printLine();
    destroyDeque(deque1);
    deleteDeque(deque2);
    destroyArray(arr);
}

// Test 4: Access element in deque.
static void cdeq_test4(void) {
    printf("\n[Test 4]\n");
    double d = 3.1415926;
    Time time = {12, 24, 48};
    CDeque deque1 = dequeList(4, varString("String"), varStruct(time, "Time"), varChar('B'), varDouble(d));
    printf("Is \'B\' in deque1? %s\n", (deqIsContain(deque1, varChar('B')) ? "Yes" : "No"));
    printf("Is \'C\' in deque1? %s\n", (deqIsContain(deque1, varChar('C')) ? "Yes" : "No"));
    printf("Index 2 in deque1: ");
    CVariant v = deqAt(deque1, 2);
    printVarData(v);
    printLine();
    printf("The head element of deque1 is: ");
    v = deqHead(deque1);
    printVarData(v);
    printLine();
    printf("The tail element of deque1 is: ");
    v = deqTail(deque1);
    printVarData(v);
    printLine();
    printf("The element \'B\' is index %d.\n", deqIndexOf(deque1, varChar('B'), 0));
    deleteDeque(deque1);
}

static void CDeque_test(void) {
    printstr("=== CDeque Test ===", '\n');
    cdeq_test1();
    cdeq_test2();
    cdeq_test3();
    cdeq_test4();
}


#endif //CCONTAINERKIT_TEST_CDEQUE_H
