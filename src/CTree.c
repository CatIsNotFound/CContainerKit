
#include "CContainerKit/CTree.h"

CTree* treeInit(void* data) {
    CTree* new_tree = (CTree*) malloc(sizeof(CTree));
    new_tree->size = (data != NULL);
    new_tree->root = createNodeT(data);
    return new_tree;
}

void destroyTree(CTree *tree, bool delete_data) {
    if (!tree) return;
    if (tree->root) {
        clearTree(tree, delete_data);
    }
    free(tree);
}

bool insertNodeToTree(CTree* tree, CNodeT* parent, bool direction, void* data) {
    if (!tree) return false;
    CNodeT* new_sub_node = createNodeT(data);
    if (!tree->root && !parent) {
        tree->root = new_sub_node;
        tree->size = 1;
        return true;
    }
    if (connectNodeT(parent, new_sub_node, direction)) {
        tree->size += 1;
        return true;
    }
    return false;
}

bool removeNodeFromTree(CTree* tree, CNodeT* node, bool delete_node) {
    if (!tree || !tree->root || !node) return false;
    if (delete_node) {
        if (!disconnectNodeT(node)) return false;
        return destroyNodeT(node, true);
    }
    bool ret = disconnectNodeT(node);
    tree->size -= ret;
    return ret;
}

void _preOrderVisit(CNodeT *node, void (*visit)(void*)) {
    if (!node) return;
    visit(node->data);
    if (node->left) _preOrderVisit(node->left, visit);
    if (node->right) _preOrderVisit(node->right, visit);
}

void _preOrderVisitByNode(CNodeT *node, void (*visit)(CNodeT*)) {
    if (!node) return;
    visit(node);
    if (node->left) _preOrderVisitByNode(node->left, visit);
    if (node->right) _preOrderVisitByNode(node->right, visit);
}

void _inOrderVisit(CNodeT *node, void (*visit)(void*)) {
    if (!node) return;
    if (node->left) _inOrderVisit(node->left, visit);
    visit(node->data);
    if (node->right) _inOrderVisit(node->right, visit);
}

void _inOrderVisitByNode(CNodeT *node, void (*visit)(CNodeT*)) {
    if (!node) return;
    if (node->left) _inOrderVisitByNode(node->left, visit);
    visit(node);
    if (node->right) _inOrderVisitByNode(node->right, visit);
}

void _postOrderVisit(CNodeT *node, void (*visit)(void*)) {
    if (!node) return;
    if (node->left) _postOrderVisit(node->left, visit);
    if (node->right) _postOrderVisit(node->right, visit);
    visit(node->data);
}

void _postOrderVisitByNode(CNodeT *node, void (*visit)(CNodeT*)) {
    if (!node) return;
    if (node->left) _postOrderVisitByNode(node->left, visit);
    if (node->right) _postOrderVisitByNode(node->right, visit);
    visit(node);
}

void forEachNodeDataFromTree(CTree* tree, OrderTraversal order, void (*visit)(void*)) {
    if (!tree || !tree->root) {
        throwError("The specified tree is not valid!");
        return;
    }
    if (order == PREORDER) {
        _preOrderVisit(tree->root, visit);
    } else if (order == INORDER) {
        _inOrderVisit(tree->root, visit);
    } else if (order == POSTORDER) {
        _postOrderVisit(tree->root, visit);
    }
}

void forEachNodeFromTree(CTree* tree, OrderTraversal order, void (*visit)(CNodeT*)) {
    if (!tree || !tree->root) {
        throwError("The specified tree is not valid!");
        return;
    }
    if (order == PREORDER) {
        _preOrderVisitByNode(tree->root, visit);
    } else if (order == INORDER) {
        _inOrderVisitByNode(tree->root, visit);
    } else if (order == POSTORDER) {
        _postOrderVisitByNode(tree->root, visit);
    }
}

void _inOrderFind(CNodeT* node, void* find_key, bool (*compare)(void*, void*), void** data) {
    if (node->left) _inOrderFind(node, find_key, compare, data);
    if (compare(find_key, node->data)) *data = node->data;
    if (node->right) _inOrderFind(node, find_key, compare, data);
}

void* findDataFromTree(CTree* tree, void* find_data, bool (*compare)(void*, void*)) {
    if (!tree || !tree->root) {
        throwError("The specified tree is not valid!");
        return NULL;
    }
    void* data = NULL;
    _inOrderFind(tree->root, find_data, compare, &data);
    return data;
}

void _clearNodeT(CNodeT* node) {
    disconnectNodeT(node);
    destroyNodeT(node, true);
}

void _clearDeleteNodeT(CNodeT* node) {
    disconnectNodeT(node);
    destroyNodeT(node, false);
}

void clearTree(CTree *tree, bool delete_data) {
    if (!tree || !tree->root) {
        throwError("The specified tree is not valid!");
        return;
    }
    _postOrderVisitByNode(tree->root, (delete_data ? _clearDeleteNodeT : _clearNodeT));
}

void _calcDepthOfTree(CNodeT* node, size_t* depth, size_t* c_depth) {
    *c_depth += 1;
    if (node->left)  _calcDepthOfTree(node->left,  depth,  c_depth);
    if (node->right) _calcDepthOfTree(node->right, depth,  c_depth);
    *depth = (*depth < *c_depth ? *c_depth : *depth);
    *c_depth -= 1;
}

size_t getDepthTree(CTree* tree) {
    if (!tree || !tree->root) return 0;
    size_t depth = 0, c_depth = 0;
    _calcDepthOfTree(tree->root, &depth, &c_depth);
    return depth;
}



