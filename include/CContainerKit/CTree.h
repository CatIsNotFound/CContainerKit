
#ifndef CCONTAINERKIT_CTREE_H
#define CCONTAINERKIT_CTREE_H

#include "CVariant.h"

typedef struct Tree CTree;
#include "CNode.h"

typedef enum OrderTraversal {
    PREORDER,
    INORDER,
    POSTORDER
} OrderTraversal;

struct Tree {
    CNodeT* root;
    size_t size;
    size_t depth;
};

CTree* treeEmpty(void);
CTree* treeRoot(CNodeT* node);
CTree* treeCreateRoot(void* data);
CTree* treeSplit(CTree* tree, CNodeT* node);
void treeMerge(CTree *root_tree, CNodeT *node, bool direction, CTree *sub_tree);
void destroyTree(CTree* tree, bool delete_data);
bool insertNodeToTree(CTree* tree, CNodeT* parent, bool direction, void* data);
bool removeNodeFromTree(CTree *tree, CNodeT *node, bool rm_node, bool rm_node_and_data);

void forEachNodeDataFromTree(CTree* tree, OrderTraversal order, void (*visit)(void*));
void forEachNodeFromTree(CTree* tree, OrderTraversal order, void (*visit)(CNodeT*));

bool isNodeFromTree(CTree *tree, CNodeT *key_node, OrderTraversal order);
CNodeT* findNodeFromTree(CTree* tree, void* find_data, bool (*compare)(void*, void*));
void* findDataFromTree(CTree* tree, void* find_data, bool (*compare)(void*, void*));
void clearTree(CTree *tree, bool delete_data);

void updateTree(CTree *tree);
bool isTreeBalanced(CTree* tree);

#define addFirstNodeToTree(tree, data)   insertNodeToTree(tree, NULL, false, data)



#endif //CCONTAINERKIT_CTREE_H
