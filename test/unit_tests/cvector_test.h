
#ifndef CVECTORSUITE_CVECTOR_TEST_H
#define CVECTORSUITE_CVECTOR_TEST_H
#include "CContainerKit/CVector.h"

typedef struct Date {
    uint16_t year;
    uint8_t mouth, day;
} Date;

// Test 1: CVector initialization test
static void cvec_test1() {
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
    destroyVector(vector1);
    destroyVector(vector2);
    destroyVector(vector3);
}

// Test 2: Conversion between CArray and CVector.
static void cvec_test2() {
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

// Test 3:
static void cvec_test3() {
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

    CArray arr_front = arrayList(3, varInt(10), varInt(20), varInt(30)),
           arr_back = arrayList(3, varString("I"), varString("Love"), varString("You"));
    vecPushFrontArray(vector, arr_front);
    vecPushBackArray(vector, arr_back);
    forEachVecElements(var, vector) {
        printVarData(var);
        printf(" ");
    }
    printf("\n");
    destroyArray(arr_front);
    destroyArray(arr_back);
    destroyVector(vector);
}

static void cvector_test() {
    printf("=== CVector Test ===\n");
    cvec_test1();
    cvec_test2();
    cvec_test3();
}

#endif //CVECTORSUITE_CVECTOR_TEST_H
