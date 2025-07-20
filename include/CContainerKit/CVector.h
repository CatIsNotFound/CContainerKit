
#pragma once
#ifndef CVECTORSUITE_CVECTOR_H
#define CVECTORSUITE_CVECTOR_H
#include "CVariant.h"
#include "CArray.h"

typedef struct Vector {
    CVariant* elements;   
    uint32_t length;      
    uint32_t capacity;    
} CVector;

CVector vectorInit(size_t length);
CVector vectorInitType(dataType data_type, size_t length);
CVector vectorList(size_t length, ...);
CVector _arrayToVector(CArray* array, bool delete_array, bool* ok);
CArray _vectorToArray(CVector* vector, bool delete_vector, bool* ok);
void _expandVector(CVector* vector);
void _resizeVector(CVector* vector, size_t new_size);
void _destroyVector(CVector* vector);
void _deleteVector(CVector* vector);
void _vectorInsert(CVector* vector, size_t index, CVariant new_value);
void _vectorInsertFromArray(CVector* vector, size_t index, CArray* array);
void _vectorRemove(CVector* vector, size_t start_pos, size_t count);
void _vectorClear(CVector *vector);
bool _vectorIsElementContain(CVector* vector, CVariant key, size_t start_pos);
size_t _vectorIndexOf(CVector *vector, CVariant element, size_t start_pos);
CVariant _vectorAt(CVector* vector, size_t index);
bool _vectorModify(CVector* vector, size_t index, CVariant new_value);
void _vectorFill(CVector* vector, size_t start_pos, uint32_t count, CVariant new_value);
CVector _vectorSubVec(CVector* vector, size_t start_pos, uint32_t count);

#define arrToVector(array, delete_array, ok)     _arrayToVector(&array, delete_array, ok)
#define vecToArray(vector, delete_vector, ok)    _vectorToArray(&vector, delete_vector, ok)
#define destroyVector(vector)                    _destroyVector(&vector)
#define deleteVector(vector)                     _deleteVector(&vector)
#define vecInsertOne(vector, index, var)         _vectorInsert(&vector, index, var)
#define vecPushBack(vector, var)                 _vectorInsert(&vector, vector.length, var);
#define vecPushFront(vector, var)                _vectorInsert(&vector, 0, var)
#define vecInsertFromArray(vector, index, array) _vectorInsertFromArray(&vector, index, &array)
#define vecAppendArray(vector, array)            _vectorInsertFromArray(&vector, vector.length, &array)
#define vecPushBackArray(vector, array)          vecAppendArray(vector, array)
#define vecPushFrontArray(vector, array)         _vectorInsertFromArray(&vector, 0, &array)
#define vecRemoveOne(vector, index)              _vectorRemove(&vector, index, 1)
#define vecRemove(vector, start_pos, count)      _vectorRemove(&vector, start_pos, count)
#define vecPopBack(vector)                       _vectorRemove(&vector, vector.length - 1, 1)
#define vecPopFront(vector)                      _vectorRemove(&vector, 0, 1)
#define vecClear(vector)                         _vectorClear(&vector)
#define vecIsContain(vector, key, start_pos)     _vectorIsElementContain(&vector, key, start_pos)
#define vecIndexOf(vector, key, start_pos)       _vectorIndexOf(&vector, key, start_pos)
#define vecAt(vector, index)                     _vectorAt(&vector, index)
#define vecModify(vector, index, new_var)        _vectorModify(&vector, index, new_var)
#define vecFill(vector, start_pos, count, var)   _vectorFill(&vector, start_pos, count, var)
#define vecFillAll(vector, var)                  _vectorFill(&vector, 0, vector.length, var)
#define vecSubVector(vector, start_pos, count)   _vectorSubVec(&vector, start_pos, count)


#define forEachVecElements(item, vector) \
    item = vector.elements[0];           \
    for (size_t i = 0; i < vector.length; ++i, item = vector.elements[i])

#define forEachVecElePtr(item, vector)    \
    item = vector->elements[0];           \
    for (size_t i = 0; i < vector->length; ++i, item = vector->elements[i])

#endif //CVECTORSUITE_CVECTOR_H
