
#include "CContainerKit/CLinkedList.h"

CLinkedList createEmptyList(void) {
    CLinkedList null_list = {NULL, NULL, 0};
    return null_list;
}

CLinkedList createList(size_t length, ...) {
    if (length == 0) return createEmptyList();
    CLinkedList new_list = createEmptyList();
    va_list var_list;
    va_start(var_list, length);
    for (size_t i = 0; i < length; ++i) {
        CVariant new_var = va_arg(var_list, CVariant);
        CNode* new_node = node(new_var);
        _pushBackNodeToList(&new_list, new_node);
    }
    va_end(var_list);
    return new_list;
}

CLinkedList createNodeList(size_t length, ...) {
    if (length == 0) return createEmptyList();
    CLinkedList new_list = createEmptyList();
    va_list var_list;
    va_start(var_list, length);
    for (size_t i = 0; i < length; ++i) {
        CNode* new_node = va_arg(var_list, CNode*);
        _pushBackNodeToList(&new_list, new_node);
    }
    va_end(var_list);
    return new_list;
}

void _clearList(CLinkedList* linked_list) {
    CNode* clear_node = linked_list->head;
    while (clear_node) {
        CNode* next_node = clear_node->next;
        _nodeModifyData(clear_node, _varEmpty(), true);
        clear_node = next_node;
    }
    linked_list->head = NULL;
    linked_list->tail = NULL;
    linked_list->length = 0;
}

void _destroyList(CLinkedList* linked_list) {
    CNode* del_node = linked_list->head;
    while (del_node) {
        CNode* next_node = del_node->next;
        _nodeRemoveOne(del_node);
        del_node = next_node;
    }
    linked_list->head = NULL;
    linked_list->tail = NULL;
    linked_list->length = 0;
}

void _pushBackNodeToList(CLinkedList* linked_list, CNode* new_node) {
    if (linked_list->length) {
        _nodeConnect(linked_list->tail, new_node);
        linked_list->tail = new_node;
    } else {
        linked_list->head = new_node;
        linked_list->tail = new_node;
    }
    linked_list->length += 1;
}

void _pushFrontNodeToList(CLinkedList* linked_list, CNode* new_node) {
    if (linked_list->length) {
        _nodeConnect(new_node, linked_list->head);
        linked_list->head = new_node;
    } else {
        linked_list->head = new_node;
        linked_list->tail = new_node;
    }
    linked_list->length += 1;
}

void _popBackNodeFromList(CLinkedList* linked_list) {
    if (linked_list->length == 0) return;
    CNode* new_tail = linked_list->tail->prev;
    _nodeRemoveOne(linked_list->tail);
    linked_list->tail = new_tail;
    linked_list->length -= 1;
}

void _popFrontNodeFromList(CLinkedList* linked_list) {
    if (linked_list->length == 0) return;
    CNode* new_head = linked_list->head->next;
    _nodeRemoveOne(linked_list->head);
    linked_list->head = new_head;
    linked_list->length -= 1;
}

void _insertNodeToList(CLinkedList* linked_list, CNode* index_node, CNode* add_new_one) {
    if (!index_node || !add_new_one) return;
    if (index_node == linked_list->head) _pushFrontNodeToList(linked_list, add_new_one);
    else if (index_node == linked_list->tail) _pushBackNodeToList(linked_list, add_new_one);
    else {
        _nodeConnect(index_node, add_new_one);
        if (add_new_one->next) {
            _nodeConnect(add_new_one, add_new_one->next);
        }
        linked_list->length += 1;
    }
}

void _removeNodeToList(CLinkedList* linked_list, CNode* remove_one) {
    if (linked_list->length == 0 || !remove_one) return;
    if (remove_one == linked_list->head) {
        _popFrontNodeFromList(linked_list);
    } else if (remove_one == linked_list->tail) {
        _popBackNodeFromList(linked_list);
    } else {
        _nodeRemoveOne(remove_one);
        linked_list->length -= 1;
    }
}

CNode* _getNodeFromList(CLinkedList* linked_list, size_t depth, bool reverse) {
    if (depth >= linked_list->length) return NULL;
    size_t current_depth = 0;
    CNode* search_node = (reverse ? linked_list->tail : linked_list->head);
    do {
        if (current_depth++ == depth) return search_node;
        search_node = (reverse ? search_node->prev : search_node->next);
    } while (search_node != NULL);
    return NULL;
}

CVariant _getNodeDataFromList(CLinkedList* linked_list, size_t depth, bool reverse) {
    CNode* ret = _getNodeFromList(linked_list, depth, reverse);
    return (ret ? ret->data : _varEmpty());
}

CNode *_findNodeFromList(CLinkedList *linked_list, CVariant *variant, bool (*compare)(CVariant, CVariant)) {
    CNode* search_node = linked_list->head;
    do {
        if (search_node->data.data_type == variant->data_type) {
            if (compare && compare(search_node->data, *variant)) return search_node;
            if (search_node->data.value == variant->value) return search_node;
        }
        search_node = search_node->next;
    } while (search_node != NULL);
    return NULL;
}

CNode *_rfindNodeFromList(CLinkedList *linked_list, CVariant *variant, bool (*compare)(CVariant, CVariant)) {
    CNode* search_node = linked_list->tail;
    do {
        if (search_node->data.data_type == variant->data_type) {
            if (compare && compare(search_node->data, *variant)) return search_node;
            if (search_node->data.value == variant->value) return search_node;
        }
        search_node = search_node->prev;
    } while (search_node != NULL);
    return NULL;
}

void _reverseList(CLinkedList* linked_list) {
    if (linked_list->length > 1) {
        CNode *cur_node = linked_list->head;
        swapNode(linked_list->head, linked_list->tail);
        while (cur_node) {
            swapNode(cur_node->prev, cur_node->next);
            cur_node = cur_node->prev;
        }
    }
}

