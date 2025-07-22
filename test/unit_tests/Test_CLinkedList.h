
#ifndef CCONTAINERKIT_TEST_CLINKEDLIST_H
#define CCONTAINERKIT_TEST_CLINKEDLIST_H

#include "CContainerKit/CLinkedList.h"

static bool compare_str(CVariant var1, CVariant var2) {
    return !strcmp(var1.value, var2.value);
}

// Test 1: Create and delete linked list.
static void clnklst_test1(void) {
    printf("[Test 1]\n");
    CNode *node1 = node(varInt(80)),
          *node2 = node(varChar('A')),
          *node3 = node(varString("Node"));
    CLinkedList lst1 = createEmptyList(),
                lst2 = createList(3, varInt(80), varChar('A'), varString("Sky")),
                lst3 = createNodeList(3, node1, node2, node3);
    printf("Length of Lists: \n");
    printf("lst1: %zu\nlst2: %zu\nlst3: %zu\n",
           lst1.length, lst2.length, lst3.length);

    destroyList(lst1);
    destroyList(lst2);
    destroyList(lst3);
}

// Test 2: Addition and deletion of node from linked list.
static void clnklst_test2(void) {
    Date d = {2025, 7, 22};
    float f = 3.1415926f;
    printf("\n[Test 2]\n");
    CNode *node1 = node(varInt(80)),
          *node2 = node(varString("Node")),
          *node3 = node(varStruct(d, "Date"));
    CLinkedList lst1 = createEmptyList(),
                lst2 = createList(5, varInt(80), varBool(false), varFloat(f),
                                  varChar('A'), varString("Sky"));
    // Add some nodes in list1
    pushBackNodeToList(lst1, node1);
    pushFrontNodeToList(lst1, node2);
    insertNodeToList(lst1, lst1.tail->prev, node3);
    // Remove some nodes in list2
    removeNodeFromList(lst2, lst2.head);
    popBackNodeFromList(lst2);
    popFrontNodeFromList(lst2);
    printf("Datas of Lists: \n");
    printf("lst1: \n");
    CNode* temp_node;
    forEachListNodePtr(temp_node, lst1) {
        printf("[%zu] ", _idx);
        printVarData(temp_node->data);
        printf(" ");
    }
    printf("\nlst2: \n");
    forEachListNodePtr(temp_node, lst2) {
        printf("[%zu] ", _idx);
        printVarData(temp_node->data);
        printf(" ");
    }
    printLine();
    printf("Length of Lists: \n");
    printf("lst1: %zu\nlst2: %zu\n",
           lst1.length, lst2.length);
    destroyList(lst1);
    destroyList(lst2);
}

// Test 3: Modify, find, access the specified node.
static void clnklst_test3(void) {
    Date d = {2025, 7, 22};
    float f = 3.1415926f;
    printf("\n[Test 2]\n");
    CNode *node1 = node(varInt(80)),
            *node2 = node(varString("Node")),
            *node3 = node(varStruct(d, "Date"));
    CVariant origin_str = varString("Sky");
    CLinkedList lst1 = createNodeList(3, node1, node2, node3),
            lst2 = createList(5, varInt(80), varBool(false), varFloat(f),
                              varChar('A'), origin_str);
    CNode* find_key1 = getNodeFromList(lst1, 2, false);
    CNode* find_key2 = getNodeFromList(lst2, 2, true);
    printf("Get Depth 2 of List 1: ");
    printVarData(find_key1->data);
    printf("\nGet Depth 2 of List 1: ");
    printVarData(find_key2->data);
    printf("\nGet List 1:\n");
    for (size_t i = 0; i < lst1.length; ++i) {
        CVariant v = getNodeDataFromList(lst1, i, false);
        printf("[%zu] ", i);
        printVarData(v);
        printf(" ");
    }
    modifyNodeData(find_key1, varString("New Value"), true);
    modifyNodeDataFromList(lst1, 1, varInt(2025), true, true);
    printf("\nGet List 1: (after modified)\n");
    for (size_t i = 0; i < lst1.length; ++i) {
        CVariant v = getNodeDataFromList(lst1, i, false);
        printf("[%zu] ", i);
        printVarData(v);
        printf(" ");
    }
    printf("\nGet List 2:\n");
    CNode* temp_node = NULL;
    forEachListNodePtr(temp_node, lst2) {
        CVariant v = temp_node->data;
        printf("[%zu] ", _idx);
        printVarData(v);
        printf(" ");
    }
    float f2 = 1.234f;
    CVariant find_key3 = varFloat(f);
    CVariant find_key4 = varFloat(f2);
    CVariant find_key5 = varString("Sky");
    printf("\nCan find 3.141592? %s\n", (findOneFromList(lst2, &find_key3) ? "Yes" : "No"));
    printf("Can find 1.234? %s\n", (findOneFromList(lst2, &find_key4) ? "Yes" : "No"));
    printf("If not use compare function: \n");
    printf("- Can find \"Sky\" (Is not a same address)? %s\n", (rfindOneFromList(lst2, &find_key5) ? "Yes" : "No"));
    printf("- Can find \"Sky\" (Is a same address)? %s\n", (rfindOneFromList(lst2, &origin_str) ? "Yes" : "No"));
    printf("If use compare function: \n");
    printf("- Can find \"Sky\" (Is not a same address)? %s\n", (findOneFromListCmp(lst2, &find_key5, compare_str) ? "Yes" : "No"));
    printf("- Can find \"Sky\" (Is a same address)? %s\n", (rfindOneFromListCmp(lst2, &origin_str, compare_str) ? "Yes" : "No"));
    varDestroy(find_key5);

    printf("\nReversed List 2: \n");
    reverseList(lst2);
    forEachListNodePtr(temp_node, lst2) {
        CVariant v = temp_node->data;
        printf("[%zu] ", _idx);
        printVarData(v);
        printf(" ");
    }
    printLine();
    destroyList(lst1);
    destroyList(lst2);

}



static void CLinkedList_Test(void) {
    printf("=== CLinkedList Test ===\n");
    clnklst_test1();
    clnklst_test2();
    clnklst_test3();

}

#endif //CCONTAINERKIT_TEST_CLINKEDLIST_H
