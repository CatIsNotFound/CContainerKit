
#include "CContainerKit/CNode.h"

CNode* createNode(CVariant data) {
    CNode* new_node = (CNode*) malloc(sizeof(CNode));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

void destroyNode(CNode* node) {
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

void nodeModifyData(CNode *node, CVariant data, bool delete_original_data) {
    if (!node) return;
    if (delete_original_data) {
        varDestroy(node->data);
    }
    node->data = data;
}

CVariant nodeData(CNode* node) {
    return (node ? node->data : varEmpty());
}

void nodeConnect(CNode* node1, CNode* node2) {
    if (!node1 || !node2) {
        throwError("Node Error: node1 or node2 is null.");
        return;
    }
    if (node1->next) {
        throwError("Node Error: node1\'s next is already exist!");
        return;
    }
    if (node2->prev) {
        throwError("Node Error: node2\'s previous is already exist!");
        return;
    }
    node2->prev = node1;
    node1->next = node2;
}

void nodeRemoveOne(CNode *node) {
    if (!node) {
        throwError("Node Error: The specified node is not valid!");
        return;
    }
    destroyNode(node);
}

CVariant nodeRelease(CNode* node) {
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

CNodeT *createNodeT(void *data) {
    CNodeT* new_node = (CNodeT*) malloc(sizeof(CNodeT));
    new_node->data = data;
    new_node->head = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->owner = NULL;
    new_node->depth = 1;
    return new_node;
}

bool destroyNodeT(CNodeT *node, void** data) {
    if (node) {
        if (data) *data = node->data;
        free(node);
        return true;
    }
    return false;
}

bool deleteNodeT(CNodeT* node) {
    if (node) {
        if (node->data) {
            free(node->data);
        }
        free(node);
        return true;
    }
    return false;
}

void setDataFromNodeT(CNodeT* node, void* data, bool delete_data) {
    if (node) {
        void* old_data = NULL;
        if (delete_data) {
            old_data = node->data;
            free(old_data);
            old_data = NULL;
        }
        node->data = data;
    }
}

void* getDataFromNodeT(CNodeT* node) {
    return (node ? node->data : NULL);
}

bool connectNodeT(CNodeT* root_node, CNodeT* sub_node, bool direction) {
    if (!root_node || !sub_node) {
        throwError("NodeT Error: The root node or sub node is null!");
        return false;
    }
    if (sub_node->head) {
        throwError("NodeT Error: This child node has been connected by other nodes.");
        return false;
    }
    if (direction) {
        if (root_node->left) {
            throwError("NodeT Error: The left node of this node already exists!");
            return false;
        }
        root_node->left = sub_node;
    } else {
        if (root_node->right) {
            throwError("NodeT Error: The right node of this node already exists!");
            return false;
        }
        root_node->right = sub_node;
    }
    sub_node->head = root_node;
    sub_node->depth = root_node->depth + 1;
    return true;
}

bool disconnectNodeT(CNodeT* node) {
    if (!node) return false;
    if (node->left && node->right) {
        throwError("NodeT Error: Can't disconnect the specified node!");
        return false;
    }
    CNodeT* head = node->head;
    if (head) {
        if (head->left == node) {
            head->left = node->left;
            if (node->left) node->left->depth = head->left->depth + 1;
        }
        if (head->right == node) {
            head->right = node->right;
            if (node->right) node->right->depth = head->right->depth + 1;
        }
    }
    node->head = NULL;
    node->left = NULL;
    node->right = NULL;
    node->depth = 1;
    return true;
}

void* releaseNodeT(CNodeT* node) {
    if (!node) return NULL;
    if (node->left || node->right) {
        throwError("NodeT Error: Delete all child nodes under this node first!");
        return NULL;
    }
    CNodeT* head = node->head;
    if (head->left == node) head->left = NULL;
    if (head->right == node) head->right = NULL;
    void* data = node->data;
    free(node);
    node = NULL;
    return data;
}

static void _setOwner(CNodeT* node, CTree* tree) {
    node->owner = tree;
    if (node->left) _setOwner(node->left, tree);
    if (node->right) _setOwner(node->right, tree);
}

void _setOwnerForEachNode(CNodeT *node, CTree *tree) {
    if (!node || !tree) {
        throwError("NodeT Error: The specified node or tree is not valid!");
        return;
    }
    _setOwner(node, tree);
}

void _swapDataNodeT(CNodeT** node1, CNodeT** node2) {
    CNodeT* temp1_node = *node1;
    CNodeT* temp2_node = *node2;
    void* temp_data = temp1_node->data;
    temp1_node->data = temp2_node->data;
    temp2_node->data = temp_data;
}

void _swapNodeT(CNodeT** node1, CNodeT** node2) {
    if (!node1 || !node2 || !*node1 || !*node2) return; 
    CNodeT* temp1_node = *node1;
    CNodeT* temp2_node = *node2;
    CTree* temp_owner = temp1_node->owner;
    temp1_node->owner = temp2_node->owner;
    temp2_node->owner = temp_owner; 

    void* temp_data = temp1_node->data;
    temp1_node->data = temp2_node->data;
    temp2_node->data = temp_data;

    CNodeT* temp_left = temp1_node->left;
    CNodeT* temp_right = temp1_node->right;
    temp1_node->left = temp2_node->left;
    temp1_node->right = temp2_node->right;
    temp2_node->left = temp_left;
    temp2_node->right = temp_right;

    if (temp1_node->left) temp1_node->left->head = temp1_node;
    if (temp1_node->right) temp1_node->right->head = temp1_node;
    if (temp2_node->left) temp2_node->left->head = temp2_node;
    if (temp2_node->right) temp2_node->right->head = temp2_node;

    CNodeT* temp_head = temp1_node->head;
    temp1_node->head = temp2_node->head;
    temp2_node->head = temp_head;

    if (temp1_node->head) {
        if (temp1_node->head->left == temp2_node) temp1_node->head->left = temp1_node;
        else if (temp1_node->head->right == temp2_node) temp1_node->head->right = temp1_node;
    } else {
        if (temp1_node->owner) temp1_node->owner->root = temp1_node;
    }

    if (temp2_node->head) {
        if (temp2_node->head->left == temp1_node) temp2_node->head->left = temp2_node;
        else if (temp2_node->head->right == temp1_node) temp2_node->head->right = temp2_node;
    } else {
        if (temp2_node->owner) temp2_node->owner->root = temp2_node;
    }

    temp1_node->depth = temp1_node->head ? (temp1_node->head->depth + 1) : 0;
    temp2_node->depth = temp2_node->head ? (temp2_node->head->depth + 1) : 0;

    if (!temp1_node->head && temp1_node->owner) updateTree(temp1_node->owner);
    if (!temp2_node->head && temp2_node->owner) updateTree(temp2_node->owner);
}

