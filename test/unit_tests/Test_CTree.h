
#ifndef CCONTAINERKIT_TEST_CTREE_H
#define CCONTAINERKIT_TEST_CTREE_H
#include "CContainerKit/CTree.h"

void print_char(CNodeT* n) {
    printf("%c(D%zu) ", (char)(int64_t)n->data, n->depth);
}

// Test 1: Basic
static void ctree_test1(void) {
    CTree* tree = treeCreateRoot((void*)'A');
    insertNodeToTree(tree, tree->root, true, (void*)'B');
    insertNodeToTree(tree, tree->root, false, (void*)'E');
    insertNodeToTree(tree, tree->root->left, true, (void*)'C');
    insertNodeToTree(tree, tree->root->left, false, (void*)'D');
    insertNodeToTree(tree, tree->root->right, true, (void*)'F');
    insertNodeToTree(tree, tree->root->right, false, (void*)'G');
    removeNodeFromTree(tree, tree->root->right->left, true, false);
    removeNodeFromTree(tree, tree->root->right->right, true, false);
    setDataFromNodeT(tree->root, (void *)'R', false);
    printf("Tree Size: %zu, Depth: %zu\n", tree->size, tree->depth);
    printf("Preorder Numbers: ");
    forEachNodeFromTree(tree, PREORDER, print_char);
    printf("\n");
    printf("Inorder Numbers: ");
    forEachNodeFromTree(tree, INORDER, print_char);
    printf("\n");
    printf("Postorder Numbers: ");
    forEachNodeFromTree(tree, POSTORDER, print_char);
    printf("\n");
    printf("Current tree is %sbalance!", (isTreeBalanced(tree) ? "" : "not "));
    destroyTree(tree, false);
}

// Test 2: Split and merge tree
static void ctree_test2(void) {
    CTree* sub_tree = treeEmpty();
    addFirstNodeToTree(sub_tree, (void*)'A');
    insertNodeToTree(sub_tree, sub_tree->root, true, (void*)'B');
    insertNodeToTree(sub_tree, sub_tree->root, false, (void*)'E');
    insertNodeToTree(sub_tree, sub_tree->root->left, true, (void*)'C');
    insertNodeToTree(sub_tree, sub_tree->root->left, false, (void*)'D');
    insertNodeToTree(sub_tree, sub_tree->root->right, true, (void*)'F');
    insertNodeToTree(sub_tree, sub_tree->root->right, false, (void*)'G');
    printf("Sub tree: ");
    forEachNodeFromTree(sub_tree, PREORDER, print_char);
    printf("\nSize: %zu, Depth: %zu\n", sub_tree->size, sub_tree->depth);

    printf("Main Tree (Original): ");
    CTree* main_tree = treeCreateRoot((void*)'a');
    insertNodeToTree(main_tree, main_tree->root, true, (void*)'b');
    insertNodeToTree(main_tree, main_tree->root->left, true, (void*)'c');
    insertNodeToTree(main_tree, main_tree->root->left, false, (void*)'d');
    insertNodeToTree(main_tree, main_tree->root->left->left, true, (void*)'e');
    insertNodeToTree(main_tree, main_tree->root->left->left, false, (void*)'f');
    forEachNodeFromTree(main_tree, PREORDER, print_char);
    printf("\nSize: %zu, Depth: %zu\n", main_tree->size, main_tree->depth);

    treeMerge(main_tree, main_tree->root, false, sub_tree);
    printf("Main Tree (Merged): ");
    forEachNodeFromTree(main_tree, PREORDER, print_char);
    printf("\nSize: %zu, Depth: %zu\n", main_tree->size, main_tree->depth);

    CTree* new_sub_tree = treeSplit(main_tree, main_tree->root->left->left);
    printf("Main Tree (Splitted): ");
    forEachNodeFromTree(main_tree, PREORDER, print_char);
    printf("\nSize: %zu, Depth: %zu\n", main_tree->size, main_tree->depth);

    printf("Split Tree: ");
    forEachNodeFromTree(new_sub_tree, PREORDER, print_char);
    printf("\nSize: %zu, Depth: %zu\n", new_sub_tree->size, new_sub_tree->depth);

    destroyTree(new_sub_tree, false);
    destroyTree(main_tree, false);
}

static void CTree_Test(void) {
    printf("[CTree Test]\n");
    printf("[Test 1]\n");
    ctree_test1();
    printf("\n[Test 2]\n");
    ctree_test2();
}

#endif //CCONTAINERKIT_TEST_CTREE_H
