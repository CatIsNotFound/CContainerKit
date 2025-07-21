#ifndef CVECTORSUITE_CARRAY_TEST_H
#define CVECTORSUITE_CARRAY_TEST_H
#include "CContainerKit/CArray.h"

// Test 1: Initilized and uninitialized array.
static void carr_test1(void) {
    CArray arr1 = arrayInit(5);
    CArray arr2 = arrayInitType(TYPE_INT32, 5);
    printf("[Test1] ");
    printf("[arr1] Length: %zu, sizeof: %zu\n", arr1.length, sizeof(arr1));
    for (size_t i = 0; i < arr1.length; ++i) {
        printf("[%zu] %s ", i, varTypeName(arr1.elements[i]));
    }
    printf("\n[arr2] Length: %zu, sizeof: %zu\n", arr2.length, sizeof(arr2));
    for (size_t i = 0; i < arr2.length; ++i) {
        printf("[%zu] %s ", i, varTypeName(arr2.elements[i]));
    }
    printLine();
    destroyArray(arr1);
    destroyArray(arr2);
}

// Test 2: Erased some of the elements in array.
static void carr_test2(void) {
    float v = 123.45f;
    CArray arr = arrayList(5, varInt(30), varChar('A'), varFloat(v), varEnum(TYPE_FUNCTION, "dataType"),
                           varString("Test String"));
    printf("\n[Test2] ");
    arrayErase(arr, 2, 4);
    for (size_t i = 0; i < arr.length; ++i) {
        printf("[%zu] ", i);
        printVarData(arr.elements[i]);
        printf(" %s, ", varTypeName(arr.elements[i]));
    }
    printf("\n");
    destroyArray(arr);
}

// Test 3: Modify and access the elements in array.
static void carr_test3(void) {
    printf("\n[Test3] ");
    CArray arr = arrayList(4, varString("This"), varString("Is"), varString("a"), varString("Book"));
    arrayModify(arr, 3, varString("Cow"));
    // CVariant var;
    // forEachArrElements(var, arr) {
    //     printVarData(var);
    //     printf(" ");
    // }
    for (size_t i = 0; i < arr.length; ++i) {
        printVarData(arr.elements[i]);
        printf(" ");
    }
    printf("\n");
    printf("Array at index %d: %s\n", 0, (const char*)arrayAt(arr, 0).value);
    CVariant find_key = varString("Cow"), find_key_2 = varString("Book");
    printf("\"Cow\" in arrayList at index %zu.\n", arrayIndexOf(arr, find_key, 0));
    printf("is \"Book\" exist in arrayList? %s\n", (arrayIsContain(arr, find_key_2, 0) ? "Yes" : "No"));
    _varsDestroy(2, find_key, find_key_2);
    arrayEraseAll(arr);
    printf("Length: %zu\n", arr.length);
    for (size_t i = 0; i < arr.length; ++i) {
        printVarData(arr.elements[i]);
        printf(" ");
    }
    printf("\n");
    destroyArray(arr);
}

static void CArray_test(void) {
    printf("=== CArray Test ===\n");
    carr_test1();
    carr_test2();
    carr_test3();
}

#endif //CVECTORSUITE_CARRAY_TEST_H
