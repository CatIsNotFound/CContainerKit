
#ifndef CCONTAINERKIT_TEST_CTREE_H
#define CCONTAINERKIT_TEST_CTREE_H
#include "CContainerKit/CTree.h"

void print_char(CNodeT* n) {
    printf("%c ", (char)(int64_t)n->data);
}

static void ctree_test1(void) {
    CTree* tree = treeInit((void*)'A');
    insertNodeToTree(tree, tree->root, true, (void*)'B');
    insertNodeToTree(tree, tree->root, false, (void*)'E');
    insertNodeToTree(tree, tree->root->left, true, (void*)'C');
    insertNodeToTree(tree, tree->root->left, false, (void*)'D');
    insertNodeToTree(tree, tree->root->right, true, (void*)'F');
    insertNodeToTree(tree, tree->root->right, false, (void*)'G');
    removeNodeFromTree(tree, tree->root->right->left, false);
    removeNodeFromTree(tree, tree->root->right->right, false);
    modifyFromNodeT(tree->root, (void *) 'R', false);
    printf("Tree Size: %zu, Depth: %zu\n", tree->size, getDepthTree(tree));
    printf("Preorder Numbers: ");
    forEachNodeFromTree(tree, PREORDER, print_char);
    printf("\n");
    printf("Inorder Numbers: ");
    forEachNodeFromTree(tree, INORDER, print_char);
    printf("\n");
    printf("Postorder Numbers: ");
    forEachNodeFromTree(tree, POSTORDER, print_char);
    printf("\n");
    destroyTree(tree, true);
}

static void ctree_test2(void) {
}

static void CTree_Test(void) {
    printf("[CTree Test]\n");
    printf("[Test 1]\n");
    ctree_test1();
    printf("\n[Test 2]\n");
    ctree_test2();
}

#endif //CCONTAINERKIT_TEST_CTREE_H
