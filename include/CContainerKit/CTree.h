
#ifndef CCONTAINERKIT_CTREE_H
#define CCONTAINERKIT_CTREE_H

#include "CVariant.h"
#include "CNode.h"

typedef enum OrderTraversal {
    PREORDER,
    INORDER,
    POSTORDER
} OrderTraversal;

typedef struct TreeNode {
    CNodeT* root;
    uint64_t size;
} CTree;

CTree* treeInit(void* data);
void destroyTree(CTree *tree, bool delete_data);
bool insertNodeToTree(CTree* tree, CNodeT* parent, bool direction, void* data);
bool removeNodeFromTree(CTree* tree, CNodeT* node, bool delete_node);

void forEachNodeDataFromTree(CTree* tree, OrderTraversal order, void (*visit)(void*));
void forEachNodeFromTree(CTree* tree, OrderTraversal order, void (*visit)(CNodeT*));
void* findDataFromTree(CTree* tree, void* find_data, bool (*compare)(void*, void*));
void clearTree(CTree *tree, bool delete_data);

size_t getDepthTree(CTree* tree);
#define addRootNodeToTree(tree, data)   insertNodeToTree(tree, NULL, false, data)

#endif //CCONTAINERKIT_CTREE_H
