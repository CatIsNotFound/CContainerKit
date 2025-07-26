
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
void _destroyNode(CNode* node);
void _nodeModifyData(CNode *node, CVariant data, bool delete_original_data);
CVariant _nodeData(CNode* node);
void _nodeConnect(CNode* node1, CNode* node2);
void _nodeRemoveOne(CNode *node);
CVariant _nodeRelease(CNode* node);
void _nodeSwap(CNode** node1, CNode** node2);

#define destroyNode(node)                          _destroyNode(node)
#define nodeModifyData(node, data, del_ori_var)    _nodeModifyData(node, data, del_ori_var)
#define nodeData(node)                             _nodeData(node)
#define nodeConnect(node1, node2)                  _nodeConnect(node1, node2)
#define nodeRelease(node)                          _nodeRelease(node)
#define nodeSwap(node1, node2)                     _nodeSwap(&node1, &node2)

typedef struct NodeT {
    void* data;
    struct NodeT* head;
    struct NodeT* left;
    struct NodeT* right;
} CNodeT;

CNodeT* createNodeT(void *data);
bool _destroyNodeT(CNodeT *node, bool delete_data);
void _modifyFromNodeT(CNodeT* node, void* data, bool delete_data);
void* _getDataFromNodeT(CNodeT* node);
bool _connectNodeT(CNodeT* root_node, CNodeT* sub_node, bool direction);
bool _disconnectNodeT(CNodeT* node);
void* _releaseNodeT(CNodeT* node);
void _swapNodeT(CNodeT** node1, CNodeT** node2);

#define destroyNodeT(node)                              _destroyNodeT(node)
#define modifyFromNodeT(node, data, del_data)           _modifyFromNodeT(node, data, del_data)
#define getDataFromNodeT(node)                          _getDataFromNodeT(node)
#define connectNodeT(node1, node2, direction)           _connectNodeT(node1, node2, direction)
#define releaseNodeT(node)                              _releaseNodeT(node)
#define swapNodeT(node1, node2)                         _swapNodeT(node1, node2)

#endif //CCONTAINERKIT_CNODE_H
