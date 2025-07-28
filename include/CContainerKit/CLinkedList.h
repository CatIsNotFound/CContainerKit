
#pragma once
#ifndef CCONTAINERKIT_CLINKEDLIST_H
#define CCONTAINERKIT_CLINKEDLIST_H
#include "CNode.h"

typedef struct LinkedList {
    CNode *head;
    CNode *tail;
    size_t length;
} CLinkedList;

CLinkedList createEmptyList(void);
CLinkedList createList(size_t length, ...);
CLinkedList createNodeList(size_t length, ...);

void _clearList(CLinkedList* linked_list);
void _destroyList(CLinkedList* linked_list);

void _pushBackNodeToList(CLinkedList* linked_list, CNode* new_node);
void _pushFrontNodeToList(CLinkedList* linked_list, CNode* new_node);
void _popBackNodeFromList(CLinkedList* linked_list);
void _popFrontNodeFromList(CLinkedList* linked_list);

void _insertNodeToList(CLinkedList* linked_list, CNode* index_node, CNode* add_new_one);
void _removeNodeToList(CLinkedList* linked_list, CNode* remove_one);
CNode* _getNodeFromList(CLinkedList* linked_list, size_t depth, bool reverse);
CVariant _getNodeDataFromList(CLinkedList* linked_list, size_t depth, bool reverse);
CNode *_findNodeFromList(CLinkedList *linked_list, CVariant *variant, bool (*compare)(CVariant, CVariant));
CNode *_rfindNodeFromList(CLinkedList *linked_list, CVariant *variant, bool (*compare)(CVariant, CVariant));

void _reverseList(CLinkedList* linked_list);

#define destroyList(linked_list)                            _destroyList(&linked_list)
#define insertNodeToList(linked_list, index_node, add_node) _insertNodeToList(&linked_list, index_node, add_node)
#define pushBackNodeToList(linked_list, add_node)           _pushBackNodeToList(&linked_list, add_node)
#define pushFrontNodeToList(linked_list, add_node)          _pushFrontNodeToList(&linked_list, add_node)
#define removeNodeFromList(linked_list, rm_node)            _removeNodeToList(&linked_list, rm_node)
#define popBackNodeFromList(linked_list)                    _popBackNodeFromList(&linked_list)
#define popFrontNodeFromList(linked_list)                   _popFrontNodeFromList(&linked_list)
#define getNodeFromList(linked_list, depth, reverse)        _getNodeFromList(&linked_list, depth, reverse)
#define getNodeDataFromList(linked_list, depth, reverse)    _getNodeDataFromList(&linked_list, depth, reverse)
#define findOneFromList(list, var)                          _findNodeFromList(&list, var, NULL)
#define rfindOneFromList(list, var)                         _rfindNodeFromList(&list, var, NULL)
#define findOneFromListCmp(list, var, cmp)                  _findNodeFromList(&list, var, cmp)
#define rfindOneFromListCmp(list, var, cmp)                 _rfindNodeFromList(&list, var, cmp)
#define reverseList(list)                                   _reverseList(&list)

#define modifyNodeDataFromList(linked_list, depth, new_var, del_old_var, reverse) \
    CNode* _ret_node = _getNodeFromList(&linked_list, depth, reverse);            \
    nodeModifyData(_ret_node, new_var, del_old_var);

#define forEachListNodePtr(node, linked_list) \
    node = linked_list.head;                  \
    for (size_t _idx = 0; _idx < linked_list.length; ++_idx, node = node->next)


#endif //CCONTAINERKIT_CLINKEDLIST_H
