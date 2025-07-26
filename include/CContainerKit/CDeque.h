
#pragma once
#ifndef CCONTAINERKIT_CDEQUE_H
#define CCONTAINERKIT_CDEQUE_H

#include "CVector.h"

typedef struct {
    CVector my_deque;
} CDeque;

CDeque dequeInit(uint32_t length);
CDeque dequeInitType(dataType data_type, uint32_t length);
CDeque dequeList(size_t length, ...);
CVector _deqToVector(CDeque* deque, bool delete_deque, bool* ok);
CDeque _vecToDeque(CVector* vector, bool delete_vector, bool* ok);
void _resizeDeque(CDeque* deque, uint32_t new_size);
void _destroyDeque(CDeque* deque);
void _deleteDeque(CDeque* deque);
void _dequePushBack(CDeque* deque, CVariant new_value);
void _dequePushFront(CDeque* deque, CVariant new_value);
void _dequePushBackFromArray(CDeque* deque, CArray* array);
void _dequePushFrontFromArray(CDeque* deque, CArray* array);
void _dequePopBack(CDeque* deque);
void _dequePopFront(CDeque* deque);
void _dequeClear(CDeque* deque);
bool _dequeIsElementContain(CDeque* deque, CVariant key);
CVariant _dequeAt(CDeque* deque, size_t index);
CVariant _dequeHead(CDeque* deque);
CVariant _dequeTail(CDeque* deque);
uint32_t _dequeIndexOf(CDeque* deque, CVariant key, size_t start_pos);
uint32_t _dequeSize(CDeque* deque);
uint32_t _dequeCapacity(CDeque* deque);
bool _dequeEmpty(CDeque* deque);


#define deqToVector(deque, delete_deque, ok)              _deqToVector(&deque, delete_deque, ok)
#define vecToDeque(vector, delete_vector, ok)             _vecToDeque(&vector, delete_vector, ok)
#define resizeDeque(deque, new_size)                      _resizeDeque(&deque, new_size)
#define destroyDeque(deque)                               _destroyDeque(&deque)
#define deleteDeque(deque)                                _deleteDeque(&deque)
#define deqPushFront(deque, var)                          _dequePushFront(&deque, var)
#define deqPushFrontFromArray(deque, array)               _dequePushFrontFromArray(&deque, &array)
#define deqPushBack(deque, var)                           _dequePushBack(&deque, var)
#define deqPushBackFromArray(deque, array)                _dequePushBackFromArray(&deque, &array)
#define deqPopFront(deque)                                _dequePopFront(&deque)
#define deqPopBack(deque)                                 _dequePopBack(&deque)
#define deqClear(deque)                                   _dequeClear(&deque)
#define deqIsContain(deque, key)                          _dequeIsElementContain(&deque, key)
#define deqAt(deque, index)                               _dequeAt(&deque, index)
#define deqHead(deque)                                    _dequeHead(&deque)
#define deqTail(deque)                                    _dequeTail(&deque)
#define deqIndexOf(deque, var, start_pos)                 _dequeIndexOf(&deque, var, start_pos)
#define deqSize(deque)                                    _dequeSize(&deque)
#define deqLength(deque)                                  deqSize(deque)
#define deqCapacity(deque)                                _dequeCapacity(&deque)
#define deqEmpty(deque)                                   _dequeEmpty(&deque)

#define forEachDeqElements(item, deque)          \
    item = deque.my_deque.elements[0];           \
    for (size_t i = 0; i < _dequeSize(&deque); ++i, item = deque.my_deque.elements[i])

#define forEachDeqElePtr(item, deque)             \
    item = deque->my_deque.elements[0];           \
    for (size_t i = 0; i < _dequeSize(deque); ++i, item = deque->my_deque.elements[i])

#endif //CCONTAINERKIT_CDEQUE_H
