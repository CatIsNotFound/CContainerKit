
#ifndef CVECTORSUITE_CVECTOR_TEST_H
#define CVECTORSUITE_CVECTOR_TEST_H
#include "CContainerKit/CVector.h"

typedef struct Date {
    uint16_t year;
    uint8_t mouth, day;
} Date;

// Test 1: CVector initialization test.
static void cvec_test1(void) {
    printf("[Test1]\n");
    printf("vector1: ");
    CVector vector1 = vectorInit(3);
    for (size_t i = 0; i < vector1.length; ++i) {
        printf("[%zu] %s ", i, varTypeName(vector1.elements[i]));
    }

    printf("\nvector2: ");
    CVector vector2 = vectorInitType(TYPE_STRING, 4);
    for (size_t i = 0; i < vector2.length; ++i) {
        printf("[%zu] %s ", i, varTypeName(vector2.elements[i]));
    }

    printf("\nvector3: \n");
    Date d = {2025, 7, 11};
    double v = 30.8;
    CVector vector3 = vectorList(5, varBool(false), varInt(30), varDouble(v), varString("Love"), varStruct(d, "Date"));
    for (size_t i = 0; i < vector3.length; ++i) {
        printf("    [%zu][%s]\t", i, varTypeName(vector3.elements[i]));
        if (vector3.elements[i].data_type == TYPE_STRUCT) {
            Date o_date = varStructData(vector3.elements[i], Date);
            printf("%d/%02d/%02d", o_date.year, o_date.mouth, o_date.day);
        } else {
            printVarData(vector3.elements[i]);
        }
        printf("\n");
    }
    vecFillAll(vector3, varEmpty()); 
    destroyVector(vector1);
    destroyVector(vector2);
    destroyVector(vector3);
}

// Test 2: Conversion between CArray and CVector.
static void cvec_test2(void) {
    printf("[Test2]\n");
    CArray arr = arrayList(3, varInt(30), varInt(20), varInt(60));
    CVector vec1 = arrToVector(arr, true, NULL);
    printf("Vector: ");
    for (size_t i = 0; i < vec1.length; ++i) {
        printVarData(vec1.elements[i]);
        printf(" ");
    }
    printf(" Length: %u, Capacity: %u\n", vec1.length, vec1.capacity);
    arr = vecToArray(vec1, true, NULL);
    printf("Array: ");
    for (size_t i = 0; i < arr.length; ++i) {
        printVarData(arr.elements[i]);
        printf(" ");
    }
    printf(" Length: %zu\n", arr.length);
    destroyArray(arr);
    destroyVector(vec1);
}

// Test 3: Addition and deletion of elements.
static void cvec_test3(void) {
    printf("[Test3]\n");
    CVector vector = vectorList(0);
    vecPushBack(vector, varInt(360));
    vecPushFront(vector, varString("Vector"));
    vecInsertOne(vector, 1, varBool(true));
    double v = 123.12;
    vecInsertOne(vector, 2, varDouble(v));
    vecRemoveOne(vector, 1);
    vecPopBack(vector);
    vecPopFront(vector);

    CVariant var;
    forEachVecElements(var, vector) {
        printVarData(var);
        printf(" ");
    }
    printf("\n");

    Date d1 = {2025, 07, 11};
    Date d2 = {2024, 11, 8};
    CArray arr_front = arrayList(3, varInt(10), varInt(20), varInt(30)),
           arr_middle = arrayList(2, varStruct(d1, "Date"), varStruct(d2, "Date")),
           arr_back = arrayList(3, varString("I"), varString("Love"), varString("You"));
    vecInsertFromArray(vector, 1, arr_middle);
    vecPushFrontArray(vector, arr_front);
    vecPushBackArray(vector, arr_back);
    vecRemove(vector, 1, 4);
    forEachVecElements(var, vector) {
        printf("[%zu] ", i);
        printVarData(var);
        printf(" ");
    }
    printf("| Length: %d, Capacity: %d\n", vector.length, vector.capacity);
    vecClear(vector);
    printf("(Clear) Length: %d, Capacity: %d\n", vector.length, vector.capacity);
    destroyArray(arr_front);
    destroyArray(arr_middle);
    destroyArray(arr_back);
    destroyVector(vector);
}

// Test 4: Find and replace elements.
static void cvec_test4(void) {
    printf("[Test 4]\n");
    CVariant key = varInt(20), not_found_key = varInt(40), find_key = varInt(50);
    CVector vec = vectorList(3, varInt(30), key, find_key);
    printf("Element 30 is%s in vector.\n", (vecIsContain(vec, key, 0) ? "" : "n't"));
    printf("Element 40 is%s in vector.\n", (vecIsContain(vec, not_found_key, 0) ? "" : "n't"));
    printf("The index of element 50 in the vector is %lld.\n", vecIndexOf(vec, find_key, 0));
    vecModify(vec, 2, not_found_key);
    printf("The index of 2 in the vector is ");
    CVariant v = vecAt(vec, 2);
    printVarData(v);
    printf(".");
    destroyVector(vec);
}

// Test 5: A single vector fills multiple elements.
static void cvec_test5(void) {
    printf("[Test 5]\n");
    CVariant var = varInt(0);
    CVector vec = vectorList(5, varInt(1), varInt(2), varInt(3), varInt(4), varInt(5));
    vecFill(vec, 2, 2, var);
    forEachVecElements(var, vec) {
        printf("[%zu] ", i);
        printVarData(var);
        printf(" ");
    }
    printLine();
    vecFillAll(vec, varInt(100));
    forEachVecElements(var, vec) {
        printf("[%zu] ", i);
        printVarData(var);
        printf(" ");
    }
    printLine();
    destroyVector(vec);
}

// Test 6: Get a sub-vector from a single vector.
static void cvec_test6(void) {
    printf("[Test 6]\n");
    CVector origin_vec = vectorList(5, varInt(1), varInt(2), varInt(3), varInt(4), varInt(5));
    CVector sub_vec = vecSubVector(origin_vec, 1, 3);
    printf("origin_vector: ");
    for (size_t i = 0; i < origin_vec.length; ++i) {
        printf("[%zu] ", i);
        printVarData(origin_vec.elements[i]);
        printf(" ");
    }
    printLine();
    printf("sub_vector: ");
    for (size_t i = 0; i < sub_vec.length; ++i) {
        printf("[%zu] ", i);
        printVarData(sub_vec.elements[i]);
        printf(" ");
    }

    printLine();
    destroyVector(sub_vec);
    destroyVector(origin_vec);
}

static void CVector_test(void) {
    printf("=== CVector Test ===\n");
    cvec_test1();
    cvec_test2();
    cvec_test3();
    cvec_test4();
    cvec_test5();
    cvec_test6();
}

#endif //CVECTORSUITE_CVECTOR_TEST_H
