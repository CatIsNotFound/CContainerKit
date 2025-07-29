
#include "CContainerKit/CTree.h"
#include "CContainerKit/CAlgorithm.h"

CTree* treeEmpty(void) {
    CTree* new_tree = (CTree*) malloc(sizeof(CTree));
    new_tree->size = 0;
    new_tree->depth = 0;
    new_tree->root = NULL;
    return new_tree;
}

CTree* treeRoot(CNodeT* node) {
    if (!node) return NULL;
    CTree* new_tree = (CTree*) malloc(sizeof(CTree));
    new_tree->size = 1;
    new_tree->depth = 1;
    new_tree->root = node;
    new_tree->root->owner = new_tree;
    return new_tree;
}

CTree* treeCreateRoot(void* data) {
    if (!data) return treeEmpty();
    CTree* new_tree = (CTree*) malloc(sizeof(CTree));
    new_tree->size = 1;
    new_tree->depth = 1;
    new_tree->root = createNodeT(data);
    new_tree->root->owner = new_tree;
    return new_tree;
}

CTree* treeSplit(CTree* tree, CNodeT* node) {
    if (!node) {
        throwError("CTree Error: The specified node is not valid!");
        return NULL;
    }
    if (node->owner != tree) {
        throwError("CTree Error: The specified node does not belong to the tree.");
        return NULL;
    }
    CTree* new_tree = treeRoot(node);
    if (node->head) {
        if (node->head->left == node) node->head->left = NULL;
        if (node->head->right == node) node->head->right = NULL;
        node->head = NULL;
    }
    _setOwnerForEachNode(tree->root, new_tree);
    updateTree(tree);
    updateTree(new_tree);
    return new_tree;
}

void treeMerge(CTree *root_tree, CNodeT *node, bool direction, CTree *sub_tree) {
    if (!root_tree || !sub_tree) {
        throwError("CTree Error: The specified tree is not valid!");
        return;
    }
    if (node->owner != root_tree) {
        throwError("CTree Error: The specified node does not belong to the tree.");
        return;
    }
    if (connectNodeT(node, sub_tree->root, direction)) {
        _setOwnerForEachNode(sub_tree->root, root_tree);
        sub_tree->root = NULL;
        destroyTree(sub_tree, false);
        updateTree(root_tree);
    }
}

void destroyTree(CTree* tree, bool delete_data) {
    if (!tree) return;
    if (tree->root) {
        clearTree(tree, delete_data);
    }
    free(tree);
}

bool insertNodeToTree(CTree* tree, CNodeT* parent, bool direction, void* data) {
    if (!tree) return false;
    if (!parent) {
        if (!tree->root) {
            tree->root = createNodeT(data);
            tree->size = 1;
            tree->root->owner = tree;
            tree->depth = 1;
            return true;
        } else {
            throwError("CTree Error: The root node is already exist! "
                       "Try to use `setDataFromNodeT()` function.");
            return false;
        }
    }
    if (parent->owner != tree) {
        throwError("CTree Error: The specified node does not belong to the tree.");
        return false;
    }
    CNodeT* new_sub_node = createNodeT(data);
    new_sub_node->owner = tree;
    if (connectNodeT(parent, new_sub_node, direction)) {
        tree->size += 1;
        tree->depth = (tree->depth < new_sub_node->depth ? new_sub_node->depth : tree->depth);
        return true;
    }
    free(new_sub_node);
    return false;
}

bool removeNodeFromTree(CTree *tree, CNodeT *node, bool rm_node, bool rm_node_and_data) {
    if (!tree || !tree->root || !node) {
        throwError("CTree Error: The specified tree or node is not valid!");
        return false;
    }
    if (node->owner != tree) {
        throwError("CTree Error: The specified node does not belong to the tree.");
        return false;
    }
    bool ret = true;
    if (!disconnectNodeT(node)) return false;
    if (rm_node_and_data) {
        ret = deleteNodeT(node);
    } else if (rm_node) {
        ret = destroyNodeT(node, NULL);
    }
    updateTree(tree);
    return ret;
}

static void _preOrderVisit(CNodeT *node, void (*visit)(void*)) {
    if (!node) return;
    visit(node->data);
    if (node->left) _preOrderVisit(node->left, visit);
    if (node->right) _preOrderVisit(node->right, visit);
}

static void _preOrderVisitByNode(CNodeT *node, void (*visit)(CNodeT*)) {
    if (!node) return;
    visit(node);
    if (node->left) _preOrderVisitByNode(node->left, visit);
    if (node->right) _preOrderVisitByNode(node->right, visit);
}

static void _inOrderVisit(CNodeT *node, void (*visit)(void*)) {
    if (!node) return;
    if (node->left) _inOrderVisit(node->left, visit);
    visit(node->data);
    if (node->right) _inOrderVisit(node->right, visit);
}

static void _inOrderVisitByNode(CNodeT *node, void (*visit)(CNodeT*)) {
    if (!node) return;
    if (node->left) _inOrderVisitByNode(node->left, visit);
    visit(node);
    if (node->right) _inOrderVisitByNode(node->right, visit);
}

static void _postOrderVisit(CNodeT *node, void (*visit)(void*)) {
    if (!node) return;
    if (node->left) _postOrderVisit(node->left, visit);
    if (node->right) _postOrderVisit(node->right, visit);
    visit(node->data);
}

static void _postOrderVisitByNode(CNodeT *node, void (*visit)(CNodeT*)) {
    if (!node) return;
    if (node->left) _postOrderVisitByNode(node->left, visit);
    if (node->right) _postOrderVisitByNode(node->right, visit);
    visit(node);
}

void forEachNodeDataFromTree(CTree* tree, OrderTraversal order, void (*visit)(void*)) {
    if (!tree || !tree->root) {
        throwError("CTree Error: The specified tree is not valid!");
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
        throwError("CTree Error: The specified tree is not valid!");
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

static void _PRCompareNode(CNodeT* current_node, CNodeT* key_node, CNodeT** find_out) {
    *find_out = (current_node == key_node ? current_node : NULL);
    if (!(*find_out) && current_node->left) _PRCompareNode(current_node->left, key_node, find_out);
    if (!(*find_out) && current_node->right) _PRCompareNode(current_node->right, key_node, find_out);
}

static void _INCompareNode(CNodeT* current_node, CNodeT* key_node, CNodeT** find_out) {
    if (!(*find_out) && current_node->left) _INCompareNode(current_node->left, key_node, find_out);
    *find_out = (current_node == key_node ? current_node : NULL);
    if (!(*find_out) && current_node->right) _INCompareNode(current_node->right, key_node, find_out);
}

static void _POCompareNode(CNodeT* current_node, CNodeT* key_node, CNodeT** find_out) {
    if (!(*find_out) && current_node->left) _POCompareNode(current_node->left, key_node, find_out);
    if (!(*find_out) && current_node->right) _POCompareNode(current_node->right, key_node, find_out);
    *find_out = (current_node == key_node ? current_node : NULL);
}

bool isNodeFromTree(CTree *tree, CNodeT *key_node, OrderTraversal order) {
    if (!tree || !key_node) {
        throwError("CTree Error: The specified tree or node is not valid!");
        return false;
    }
    CNodeT* ret = NULL;
    if (order == PREORDER) _PRCompareNode(tree->root, key_node, &ret);
    if (order == INORDER) _INCompareNode(tree->root, key_node, &ret);
    if (order == POSTORDER) _POCompareNode(tree->root, key_node, &ret);
    return (ret != NULL);
}

static void _inOrderFind(CNodeT* node, void* find_key, bool (*compare)(void*, void*), CNodeT** data) {
    if (node->left) _inOrderFind(node, find_key, compare, data);
    if ((compare && compare(find_key, node->data)) ||
        (find_key == node->data)) *data = node;
    if (node->right) _inOrderFind(node, find_key, compare, data);
}

CNodeT* findNodeFromTree(CTree* tree, void* find_data, bool (*compare)(void*, void*)) {
    if (!tree || !tree->root) {
        throwError("CTree Error: The specified tree is not valid!");
        return NULL;
    }
    CNodeT* node = NULL;
    _inOrderFind(tree->root, find_data, compare, &node);
    return node;
}

void* findDataFromTree(CTree* tree, void* find_data, bool (*compare)(void*, void*)) {
    if (!tree || !tree->root) {
        throwError("CTree Error: The specified tree is not valid!");
        return NULL;
    }
    CNodeT* node = NULL;
    _inOrderFind(tree->root, find_data, compare, &node);
    return (node ? node->data : NULL);
}

static void _clearNodeT(CNodeT* node) {
    destroyNodeT(node, NULL);
}

static void _clearDeleteNodeT(CNodeT* node) {
    deleteNodeT(node);
}

void clearTree(CTree *tree, bool delete_data) {
    if (!tree || !tree->root) {
        throwError("CTree Error: The specified tree is not valid!");
        return;
    }
    _postOrderVisitByNode(tree->root, (delete_data ? _clearDeleteNodeT : _clearNodeT));
}

static void _calcTree(CNodeT* node, size_t* depth, size_t* size, size_t* c_depth) {
    *c_depth += 1;
    *size += 1;
    node->depth = *c_depth;
    if (node->left) _calcTree(node->left, depth, size, c_depth);
    if (node->right) _calcTree(node->right, depth, size, c_depth);
    *depth = (*depth < *c_depth ? *c_depth : *depth);
    *c_depth -= 1;
}

void updateTree(CTree *tree) {
    if (!tree || !tree->root) return;
    size_t new_depth = 0, c_depth = 0, new_size = 0;
    _calcTree(tree->root, &new_depth, &new_size, &c_depth);
    tree->depth = new_depth;
    tree->size = new_size;
}

static void _check_node(CNodeT* node, size_t* depth, size_t* max_depth) {
    *depth += 1;
    if (node->left) _check_node(node->left, depth, max_depth);
    if (node->right) _check_node(node->right, depth, max_depth);
    *max_depth = (*max_depth < *depth ? *depth : *max_depth);
    *depth -= 1;
}

static bool _checkParentIsBalanced(CNodeT* node, size_t* max_depth) {
    if (!node) return false;
    size_t d_left = 0, d_right = 0, m_left = 0, m_right = 0;
    if (node->left) _check_node(node->left, &d_left, &m_left);
    if (node->right) _check_node(node->right, &d_right, &m_right);
    *max_depth = (m_left < m_right ? m_right : m_left);
    return abs_size_t(m_left, m_right) <= 1;
}

bool isTreeBalanced(CTree* tree) {
    if (!tree || !tree->root) {
        throwError("CTree Error: The specified tree is not valid!");
        return false;
    }
    size_t max_left = 0, max_right = 0;
    bool b1 = _checkParentIsBalanced(tree->root->left, &max_left);
    if (!b1) return false;
    bool b2 = _checkParentIsBalanced(tree->root->right, &max_right);
    if (!b2) return false;
    return abs_size_t(max_left, max_right) <= 1;
}


