
#ifndef CCONTAINERKIT_TEST_CSTRING_H
#define CCONTAINERKIT_TEST_CSTRING_H
#include "CContainerKit/CString.h"
#include "CContainerKit/CDebug.h"

// Test 1: Initialization, addition and deletion of strings.
static void cstr_test1() {
    CString str1 = string("Hello");
    CString str2 = strInit('C', 3);
    CString str3 = strList(" ", 4, "Hello,", "I", "am", "Tom!");
    stringPushBack(str1, " world!");
    stringPushFront(str1, "$$$");
    stringPushFront(str2, "Apple");
    stringAppend(str2, "Banana");
    stringPopFront(str3, 7);
    stringPopBack(str3, 4);
    stringPushBack(str3, "Jerry!");
    printstr("[Test 1]", '\n');
    printstrs(true, true, 6, "str1:", str1.data, "str2:", str2.data, "\nstr3:", str3.data);
    printstr("Length: ", ' ');
    printf("str1: %d, str2: %d, str3: %d\n", str1.length, str2.length, str3.length);
    printstr("Capacity: ", ' ');
    printf("str1: %d, str2: %d, str3: %d\n", str1.capacity, str2.capacity, str3.capacity);
    destroyString(str1);
    destroyString(str2);
    destroyString(str3);
}

// Test 2: Copy and get sub string
static void cstr_test2() {
    CString str_root = string("Where there is a will, there is a way!");
    CString str_sc = stringSub(str_root, 6, 5);
    stringCopy(str_sc, "One day one apple, doctor keep me away!");
    printstr("\n[Test 2]", '\n');
    printf("str1: %s\nstr2[6, 10]: %s\n", str_root.data, str_sc.data);
    printf("Length: str1 %d, str2 %d; Capacity: str1 %d, str2 %d\n",
           str_root.length, str_sc.length, str_root.capacity, str_sc.capacity);
    destroyString(str_root);
    destroyString(str_sc);
}

// Test 3: Compare, contain, Case conversion
static void cstr_test3() {
    CString str = string("Sample Text!");
    bool b1 = stringIsEqual(str, "sample text!", false),
         b2 = stringIsEqual(str, "sample text!", true);
    printstr("\n[Test 3]", '\n');
    printf("String: %s\n", str.data);
    printf("Is euqal: %s\n", (b1 ? "Yes" : "No"));
    printf("Is euqal (case_sensitive): %s\n", (b2 ? "Yes" : "No"));

    bool b3 = stringIsContain(str, "text", false),
         b4 = stringIsContain(str, "text", true);
    printf("Is contain \"text\": %s\n", (b3 ? "Yes" : "No"));
    printf("Is contain \"text\" (case_sensitive): %s\n", (b4 ? "Yes" : "No"));

    stringUpper(str);
    printf("Upper String: %s\n", str.data);
    stringLower(str);
    printf("Lower String: %s\n", str.data);
    destroyString(str);
}

// Test 4: Split and Vector
static void cstr_test4() {
    printstr("\n[Test 4]", '\n');
    CString str = string("Where there is a will, there is a way!");
    CVector vec1 = stringSplit(str, ' '),
            vec2 = stringToVector(str);
    CVariant v;
    printf("vec1: ");
    for (size_t i = 0; i < vec1.length; ++i) {
        printf("[%zu] %s (%s)\n", i, varStringData(vec1.elements[i]), varTypeName(vec1.elements[i]));
    }
    printf("\nLength: %d, Capacity: %d\n", vec1.length, vec1.capacity);
    printf("\nvec2: ");
    forEachVecElements(v, vec2) {
        printf("%c", varCharData(v));
        if (i < vec2.length - 1) printf("|");
    }
    printf("\nLength: %d, Capacity: %d\n", vec2.length, vec2.capacity);
    destroyString(str);
    destroyVector(vec1);
    destroyVector(vec2);
}

static void CString_test() {
    printstr("=== CString Test ===", '\n');
    cstr_test1();
    cstr_test2();
    cstr_test3();
    cstr_test4();
}


#endif //CCONTAINERKIT_TEST_CSTRING_H
