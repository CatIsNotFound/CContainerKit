
#ifndef CCONTAINERKIT_TEST_CSTACK_H
#define CCONTAINERKIT_TEST_CSTACK_H
#include "CContainerKit/CStack.h"

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} Time;

// Test 1: CStack initialization test.
static void cstk_test1(void) {
    printf("[Test 1]\n");
    double d = 123.45;
    const char s[] = "CStack";
    CStack stack1 = stackInit(3),
           stack2 = stackInitType(TYPE_INT32, 5),
           stack3 = stackList(4, varULongLong(1234567890), varChar('A'), varDouble(d), varString(s));

    CVariant var;
    printf("stack1: ");
    forEachStkElements(var, stack1) {
        printVarData(var);
        printf(" (%s) ", varTypeName(var));
    }
    printf("\nLength: %d, Capacity: %d", stkLength(stack1), stkCapacity(stack1));
    printf("\nstack2: ");
    forEachStkElements(var, stack2) {
        printVarData(var);
        printf(" (%s) ", varTypeName(var));
    }
    printf("\nLength: %d, Capacity: %d", stkLength(stack2), stkCapacity(stack2));
    printf("\nstack3: ");
    forEachStkElements(var, stack3) {
        printVarData(var);
        printf(" (%s) ", varTypeName(var));
    }
    printf("\nLength: %d, Capacity: %d", stkLength(stack3), stkCapacity(stack3));
    printLine();
    destroyStack(stack1);
    destroyStack(stack2);
    deleteStack(stack3);
}

// Test 2: Conversion between CStack and CVector.
static void cstk_test2(void) {
    printf("\n[Test 2]\n");
    CStack stack1 = stackList(3, varChar('A'), varInt(8888), varString("Stack To Vector"));
    CVector vector1 = stkToVector(stack1, true, NULL);
    CVariant var;
    printf("stack to vector: ");
    forEachVecElements(var, vector1) {
        printVarData(var);
        printf("(%s) | ", varTypeName(var));
    }
    printLine();
    float f = 123.45f;
    CVector vector2 = vectorList(3, varInt(50), varFloat(f), varString("Vector To Stack"));
    CStack stack2 = vecToStack(vector2, true, NULL);
    printf("vector to stack: ");
    forEachStkElements(var, stack2) {
        printVarData(var);
        printf("(%s) | ", varTypeName(var));
    }
    printLine();
    destroyVector(vector1);
    destroyStack(stack2);
}

// Test 3: Resize, Addition and deletion of elements.
static void cstk_test3(void) {
    printf("\n[Test 3]\n");
    CStack stack1 = stackInit(5);
    printf("[Stack 1] length: %d, capacity: %d\n", stkLength(stack1), stkCapacity(stack1));
    resizeStack(stack1, 30);
    printf("[Stack 1 Resized] length: %d, capacity: %d\n", stkLength(stack1), stkCapacity(stack1));
    stkClear(stack1);
    printf("[Stack 1 Clear] length: %d, capacity: %d\n", stkLength(stack1), stkCapacity(stack1));
    printLine();
    float f = 1.234f;
    CStack stack2 = stackList(5, varChar('#'), varUChar('P'), varShort(1024), varFloat(f), varString("qwerty"));
    CArray arr = arrayList(5, varInt(30), varChar('A'), varFloat(f), varEnum(TYPE_STRUCT, "dataType"),
                           varString("Test String"));
    stkPop(stack2);
    Time time = {10, 20, 30};
    stkPush(stack2, varStruct(time, "Time"));
    stkPushFromArray(stack2, arr);
    printf("[Stack 2] length: %d, capacity: %d\n",
           stkLength(stack2), stkCapacity(stack2));
    CVariant var;
    forEachStkElements(var, stack2) {
        printVarData(var);
        printf(" (%s) | ", varTypeName(var));
    }
    printLine();
    destroyStack(stack1);
    deleteStack(stack2);
    destroyArray(arr);
}

// Test 4: Access element in stack.
static void cstk_test4(void) {
    printf("\n[Test 4]\n");
    double d = 3.1415926;
    Time time = {12, 24, 48};
    CStack stack1 = stackList(4, varString("String"), varStruct(time, "Time"), varChar('B'), varInt(666666));
    printf("Is \'B\' in stack1? %s\n", (stkIsContain(stack1, varChar('B')) ? "Yes" : "No"));
    printf("Is \'C\' in stack1? %s\n", (stkIsContain(stack1, varChar('C')) ? "Yes" : "No"));
    printf("Index 2 in stack1: ");
    CVariant v = stkAt(stack1, 2);
    printVarData(v);
    printLine();
    printf("The Top element of stack1 is: ");
    v = stkTop(stack1);
    printVarData(v);
    printLine();
    printf("The element \'B\' is index %d.\n", stkIndexOf(stack1, varChar('B'), 0));

}

static void CStack_test(void) {
    printstr("=== CStack Test ===", '\n');
    cstk_test1();
    cstk_test2();
    cstk_test3();
    cstk_test4();
}

#endif //CCONTAINERKIT_TEST_CSTACK_H
