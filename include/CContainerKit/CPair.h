
#pragma once
#ifndef CCONTAINERKIT_CPAIR_H
#define CCONTAINERKIT_CPAIR_H
#include "CVariant.h"

typedef enum KeyType {
    KEY_INT,
    KEY_STRING,
    KEY_POINTER,
    KEY_CUSTOM
} KeyType;

typedef struct Pair {
    void* key;
    CVariant value;
} CPair;

CPair pair(void* key, CVariant value);
void _destroyPair(CPair* pair);
void _deletePair(CPair* pair);
void _swapPair(CPair* pair1, CPair* pair2);
bool _comparePair(CPair* pair1, CPair* pair2, bool (*compare)(CVariant, CVariant));
bool _isKeyEqualPair(CPair* pair1, CPair* pair2, bool (*compare)(void*, void*));

#define destroyPair(pair)                                   _destroyPair(&pair)
#define deletePair(pair)                                    _deletePair(&pair)
#define swapPair(pair1, pair2)                              _swapPair(&pair1, &pair2)
#define comparePair(pair1, pair2, compare)                  _comparePair(&pair1, &pair2, compare)
#define isKeyEqualPair(pair1, pair2, compare)               _isKeyEqualPair(&pair1, &pair2, compare)

#endif //CCONTAINERKIT_CPAIR_H
