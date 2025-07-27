
#pragma once
#ifndef CCONTAINERKIT_CNODE_H
#define CCONTAINERKIT_CNODE_H
#include "CVariant.h"

typedef struct Node {
    CVariant data;
    struct Node *prev;
    struct Node *next;
} CNode;

CNode* createNode(CVariant data);
void destroyNode(CNode* node);
void nodeModifyData(CNode *node, CVariant data, bool delete_original_data);
CVariant nodeData(CNode* node);
void nodeConnect(CNode* node1, CNode* node2);
void nodeRemoveOne(CNode *node);
CVariant nodeRelease(CNode* node);
void _nodeSwap(CNode** node1, CNode** node2);

#define nodeSwap(node1, node2)                     _nodeSwap(&node1, &node2)

typedef struct NodeT {
    void* data;
    struct NodeT* head;
    struct NodeT* left;
    struct NodeT* right;
} CNodeT;

CNodeT* createNodeT(void *data);
bool destroyNodeT(CNodeT *node, bool delete_data);
void modifyFromNodeT(CNodeT* node, void* data, bool delete_data);
void* getDataFromNodeT(CNodeT* node);
bool connectNodeT(CNodeT* root_node, CNodeT* sub_node, bool direction);
bool disconnectNodeT(CNodeT* node);
void* releaseNodeT(CNodeT* node);
void _swapNodeT(CNodeT** node1, CNodeT** node2);

#define swapNodeT(node1, node2)                         _swapNodeT(&node1, &node2)

#endif //CCONTAINERKIT_CNODE_H
