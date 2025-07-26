
#pragma once
#ifndef CVECTORSUITE_CARRAY_H
#define CVECTORSUITE_CARRAY_H
#include "CVariant.h"

typedef struct Array {
    CVariant* elements;   
    size_t    length;     
} CArray;

CArray arrayInit(size_t length);
CArray arrayInitType(dataType data_type, size_t length);
CArray arrayList(size_t length, ...);
void _deleteArray(CArray* array);
void _destroyArray(CArray* array);
void _arrayExpand(CArray *array, size_t length);
void _arrayErase(CArray* array, size_t start_pos, size_t end_pos);
void _arrayEraseAll(CArray* array);
bool _arrayIsElementEqual(CArray *array, CVariant key_element, size_t start_pos, bool (*compare)(CVariant, CVariant));
size_t _arrayIndexOf(CArray *array, CVariant element, size_t start_pos);
CVariant _arrayAt(CArray* array, size_t index);
bool _arrayModify(CArray* array, size_t index, CVariant value);

#define deleteArray(array)                       _deleteArray(&array)
#define destroyArray(array)                      _destroyArray(&array)
#define arrayExpand(array, new_length)           _arrayExpand(&array, new_length)
#define arrayErase(array, start_pos, end_pos)    _arrayErase(&array, start_pos, end_pos)
#define arrayEraseAll(array)                     _arrayEraseAll(&array)
#define arrayIsEqual(array, key, pos, cmp)       _arrayIsElementEqual(&array, key, pos, cmp)
#define arrayIsContain(array, key, pos)          _arrayIsElementEqual(&array, key, pos, NULL)
#define arrayIndexOf(array, element, pos)        _arrayIndexOf(&array, element, pos)
#define arrayAt(array, index)                    _arrayAt(&array, index)
#define arrayModify(array, index, value)         _arrayModify(&array, index, value)

#define forEachArrElements(item, array) \
    item = array.elements[0];           \
    for (size_t i = 0; i < array.length; ++i, item = array.elements[i])

#define forEachArrElePtr(item, array) \
    item = array->elements[0];           \
    for (size_t i = 0; i < array->length; ++i, item = array->elements[i])

#endif //CVECTORSUITE_CARRAY_H
