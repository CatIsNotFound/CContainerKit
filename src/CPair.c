
#include "CContainerKit/CPair.h"

CPair pair(void* key, CVariant value) {
    CPair new_pair;
    new_pair.key = key;
    new_pair.value = value;
    return new_pair;
}

void _destroyPair(CPair* pair) {
    // varDestroy(pair->key);
}

void _deletePair(CPair* pair) {
    // varDestroy(pair->key);
    varDestroy(pair->value);
}

void _swapPair(CPair* pair1, CPair* pair2) {
    if (!pair1 || !pair2) return;
    CVariant temp = pair1->value;
    pair1->value = pair2->value;
    pair2->value = temp;
}

bool _comparePair(CPair* pair1, CPair* pair2, bool (*compare)(CVariant, CVariant)) {
    if (!pair1 || !pair2) return false;
    if (compare) {
        return compare(pair1->value, pair2->value);
    } else {
        return (&pair1->value == &pair2->value);
    }
}

bool _isKeyEqualPair(CPair* pair1, CPair* pair2, bool (*compare)(void*, void*)) {
    if (!pair1 || !pair2) return false;
    if (compare) {
        return compare(pair1->key, pair2->key);
    } else {
        return pair1->key == pair2->key;
    }
}

