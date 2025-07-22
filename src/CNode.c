
#include "CContainerKit/CNode.h"

CNode* nodeCreate(CVariant data, CNode* prev, CNode* next) {
    CNode* new_node = (CNode*) malloc(sizeof(CNode));
    new_node->data = data;
    new_node->prev = prev;
    new_node->next = next;
    return new_node;
}

void _destroyNode(CNode* node) {
    if (node->prev) {
        node->prev->next = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    node->prev = NULL;
    node->next = NULL;
    varDestroy(node->data);
    free(node);
    node = NULL;
}

bool _nodeHasNextNode(CNode* node) {
    return (node ? node->next : false);
}

bool _nodeHasPreviousNode(CNode* node) {
    return (node ? node->prev : false);
}

void _nodeModifyData(CNode *node, CVariant data, bool delete_original_data) {
    if (!node) return;
    if (delete_original_data) {
        varDestroy(node->data);
    }
    node->data = data;
}

CVariant _nodeData(CNode* node) {
    return (node ? node->data : _varEmpty());
}

void _nodeConnect(CNode* node1, CNode* node2) {
    if (!node1 || !node2) {
        throwError("Node Connection Error: node1 or node2 is null.");
        return;
    }
    if (node1->next) {
        throwError("Node Connection Error: node1\'s next is already exist!");
        return;
    }
    if (node2->prev) {
        throwError("Node Connection Error: node2\'s previous is already exist!");
        return;
    }
    node2->prev = node1;
    node1->next = node2;
}

void _nodeRemoveOne(CNode *node) {
    if (!node) {
        throwError("Node Disconnection Error: The specified node is not valid!");
        return;
    }
    _destroyNode(node);
}

CVariant _releaseNode(CNode* node) {
    CVariant var = node->data;
    if (node->prev) {
        node->prev->next = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    node->prev = NULL;
    node->next = NULL;
    free(node);
    return var;
}

void _nodeSwap(CNode** node1, CNode** node2) {
    CNode* tmp = *node1;
    *node1 = *node2;
    *node2 = tmp;
}
