
#include "CContainerKit/CDeque.h"

CDeque dequeInit(uint32_t length) {
    CDeque new_deque;
    new_deque.my_deque = vectorInit(length);
    return new_deque;
}

CDeque dequeInitType(dataType data_type, uint32_t length) {
    CDeque new_deque;
    new_deque.my_deque = vectorInitType(data_type, length);
    return new_deque;
}

CDeque dequeList(size_t length, ...) {
    CDeque new_deque;
    new_deque.my_deque = vectorInit(length);
    va_list s_list;
    va_start(s_list, length);
    for (size_t i = 0; i < length; ++i) {
        CVariant var = va_arg(s_list, CVariant);
        vecModify(new_deque.my_deque, i, var);
    }
    va_end(s_list);
    return new_deque;
}

CVector _deqToVector(CDeque* deque, bool delete_deque, bool* ok) {
    if (!deque) {
        if (ok) *ok = false;
        throwError("Deque to Vector: The specified deque is not valid!");
        return vectorInit(0);
    }
    CVector new_vector = vectorInit(_dequeSize(deque));
    CVariant var;
    forEachVecElements(var, deque->my_deque) {
        vecModify(new_vector, i, var);
    }
    if (delete_deque) {
        _destroyDeque(deque);
    }
    if (ok) *ok = true;
    return new_vector;
}

CDeque _vecToDeque(CVector* vector, bool delete_vector, bool* ok) {
    if (!vector) {
        if (ok) *ok = false;
        CDeque null_deque = dequeInit(0);
        return null_deque;
    }
    CDeque new_deque = dequeInit(vector->length);
    CVariant var;
    forEachVecElePtr(var, vector) {
        vecModify(new_deque.my_deque, i, var);
    }
    if (delete_vector) {
        _destroyVector(vector);
    }
    if (ok) *ok = true;
    return new_deque;
}

void _resizeDeque(CDeque* deque, uint32_t new_size) {
    _resizeVector(&deque->my_deque, new_size);
}

void _destroyDeque(CDeque* deque) {
    destroyVector(deque->my_deque);
}

void _deleteDeque(CDeque* deque) {
    deleteVector(deque->my_deque);
}

void _dequePushBack(CDeque* deque, CVariant new_value) {
    vecPushBack(deque->my_deque, new_value);
}

void _dequePushFront(CDeque* deque, CVariant new_value) {
    vecPushFront(deque->my_deque, new_value);
}

void _dequePushBackFromArray(CDeque* deque, CArray* array) {
    vecPushBackArray(deque->my_deque, *array);
}

void _dequePushFrontFromArray(CDeque* deque, CArray* array) {
    vecPushFrontArray(deque->my_deque, *array);
}

void _dequePopFront(CDeque* deque) {
    if (deque->my_deque.length) vecPopFront(deque->my_deque);
}

void _dequePopBack(CDeque* deque) {
    if (deque->my_deque.length) vecPopBack(deque->my_deque);
}

void _dequeClear(CDeque* deque) {
    if (deque->my_deque.length) vecClear(deque->my_deque);
}

bool _dequeIsElementContain(CDeque* deque, CVariant key) {
    return vecIsContain(deque->my_deque, key, 0);
}

CVariant _dequeAt(CDeque* deque, size_t index) {
    if (index >= deque->my_deque.length) return _varEmpty();
    return vecAt(deque->my_deque, index);
}

CVariant _dequeHead(CDeque* deque) {
    if (deque->my_deque.length) return deque->my_deque.elements[0];
    else return _varEmpty();
}

CVariant _dequeTail(CDeque* deque) {
    if (deque->my_deque.length) return deque->my_deque.elements[deque->my_deque.length - 1];
    else return _varEmpty();
}

uint32_t _dequeIndexOf(CDeque* deque, CVariant key, size_t start_pos) {
    return vecIndexOf(deque->my_deque, key, start_pos);
}

uint32_t _dequeSize(CDeque* deque) {
    return deque->my_deque.length;
}

uint32_t _dequeCapacity(CDeque* deque) {
    return deque->my_deque.capacity;
}

