
#pragma once
#ifndef CCONTAINERKIT_CNODE_H
#define CCONTAINERKIT_CNODE_H
#include "CVariant.h"

typedef struct Node {
    CVariant data;
    struct Node *prev;
    struct Node *next;
} CNode;

CNode* nodeCreate(CVariant data, CNode* prev, CNode* next);
void _destroyNode(CNode* node);
bool _nodeHasNextNode(CNode* node);
bool _nodeHasPreviousNode(CNode* node);
void _nodeModifyData(CNode *node, CVariant data, bool delete_original_data);
CVariant _nodeData(CNode* node);
void _nodeConnect(CNode* node1, CNode* node2);
void _nodeRemoveOne(CNode *node);
CVariant _releaseNode(CNode* node);
void _nodeSwap(CNode** node1, CNode** node2);

#define node(data)                                 nodeCreate(data, NULL, NULL)
#define destroyNode(node)                          _destroyNode(node)
#define hasNextNode(node)                          _nodeHasNextNode(node)
#define hasPrevNode(node)                          _nodeHasPreviousNode(node)
#define modifyNodeData(node, data, del_ori_var)    _nodeModifyData(node, data, del_ori_var)
#define nodeData(node)                             _nodeData(node)
#define nodeConnect(node1, node2)                  _nodeConnect(node1, node2)
#define releaseNode(node)                          _releaseNode(node)
#define swapNode(node1, node2)                     _nodeSwap(&node1, &node2)

#endif //CCONTAINERKIT_CNODE_H
