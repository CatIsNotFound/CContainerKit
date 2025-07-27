
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
        throwError("Connection Node: node1 or node2 is null.");
        return;
    }
    if (node1->next) {
        throwError("Connection Node: node1\'s next is already exist!");
        return;
    }
    if (node2->prev) {
        throwError("Connection Node: node2\'s previous is already exist!");
        return;
    }
    node2->prev = node1;
    node1->next = node2;
}

void nodeRemoveOne(CNode *node) {
    if (!node) {
        throwError("Disconnection Node: The specified createNode is not valid!");
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
    return new_node;
}

bool destroyNodeT(CNodeT *node, bool delete_data) {
    if (node) {
        if (node->left || node->right || node->head) {
            throwError("Destroy NodeT: The current createNode is not an independent node and cannot be deleted!");
            return false;
        }
        if (delete_data && node->data) {
            free(node->data);
        }
        node->head = NULL;
        node->left = NULL;
        node->right = NULL;
        return true;
    }
    return false;
}

void modifyFromNodeT(CNodeT* node, void* data, bool delete_data) {
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
        throwError("Connect NodeT: The root node or sub node is null!");
        return false;
    }
    if (sub_node->head) {
        throwError("Connect NodeT: This child createNode has been connected by other nodes.");
        return false;
    }
    if (direction) {
        if (root_node->left) {
            throwError("Connect NodeT: The left node of this createNode already exists!");
            return false;
        }
        root_node->left = sub_node;
    } else {
        if (root_node->right) {
            throwError("Connect NodeT: The right node of this createNode already exists!");
            return false;
        }
        root_node->right = sub_node;
    }
    sub_node->head = root_node;
    return true;
}

bool disconnectNodeT(CNodeT* node) {
    if (node->left || node->right) {
        throwError("Disconnect NodeT: Please disconnect all child nodes under this createNode first!");
        return false;
    }
    CNodeT* head = node->head;
    if (head) {
        if (head->left == node) head->left = NULL;
        if (head->right == node) head->right = NULL;
    }
    node->head = NULL;
    return true;
}

void* releaseNodeT(CNodeT* node) {
    if (node->left || node->right) {
        throwError("Release NodeT: Delete all child nodes under this createNode first!");
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

void _swapNodeT(CNodeT** node1, CNodeT** node2) {
    CNodeT* temp1_node = *node1;
    CNodeT* temp2_node = *node2;
    void* temp_data = temp1_node->data;
    temp1_node->data = temp2_node->data;
    temp2_node->data = temp_data;
}


