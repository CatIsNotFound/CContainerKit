#include "CContainerKit/CArray.h"

CArray arrayInit(size_t length) {
    CArray new_array;
    new_array.elements = (CVariant*)calloc(length, sizeof(CVariant));
    new_array.length = length;
    for (size_t i = 0; i < new_array.length; ++i) {
        new_array.elements[i].data_type = TYPE_NULL;
        new_array.elements[i].value = (void*)0;
    }
    return new_array;
}

CArray arrayInitType(dataType data_type, size_t length) {
    CArray new_array;
    new_array.elements = (CVariant*)calloc(length, sizeof(CVariant));
    for (size_t i = 0; i < length; ++i) {
        new_array.elements[i].data_type = data_type;
        new_array.elements[i].value = (void*)0;
    }
    new_array.length = length;
    return new_array;
}

CArray arrayList(size_t length, ...) {
    va_list a_list;
    CArray new_array;
    new_array.elements = (CVariant*)calloc(length, sizeof(CVariant));
    va_start(a_list, length);
    for (size_t i = 0; i < length; ++i) {
        new_array.elements[i] = va_arg(a_list, CVariant);
    }
    va_end(a_list);
    new_array.length = length;
    return new_array;
}

void _deleteArray(CArray* array) {
    if (array) {
        _arrayEraseAll(array);
        _destroyArray(array);
    }
}

void _destroyArray(CArray* array) {
    if (array && array->elements) {
        free(array->elements);
        array->elements = NULL;
        array->length = 0;
    }
}

void _arrayErase(CArray* array, size_t start_pos, size_t end_pos) {
    if (start_pos < array->length && end_pos < array->length) {
        if (start_pos > end_pos) {
            start_pos = start_pos ^ end_pos;
            end_pos = start_pos ^ end_pos;
            start_pos = start_pos ^ end_pos;
        }
        for (size_t i = start_pos; i <= end_pos; ++i) {
            varDestroy(array->elements[i]);
            array->elements[i].data_type = TYPE_NULL;
            array->elements[i].value = (void *) 0;
        }
    }
}

void _arrayEraseAll(CArray* array) {
    for (size_t i = 0; i < array->length; ++i) {
        varDestroy(array->elements[i]);
        array->elements[i] = _varEmpty();
    }
}

bool _arrayIsElementContain(CArray *array, CVariant key_element, size_t start_pos) {
    for (size_t i = start_pos; i < array->length; ++i) {
        if (key_element.data_type != array->elements[i].data_type) continue;
        if (key_element.value != array->elements[i].value) continue;
        return true;
    }
    return false;
}

size_t _arrayIndexOf(CArray *array, CVariant element, size_t start_pos) {
    for (size_t i = start_pos; i < array->length; ++i) {
        if (element.data_type != array->elements[i].data_type) continue;
        if (element.value != array->elements[i].value) continue;
        return i;
    }
    return N_POS;
}

CVariant _arrayAt(CArray* array, size_t index) {
    if (index < array->length) {
        return array->elements[index];
    }
    return _varEmpty();
}

bool _arrayModify(CArray* array, size_t index, CVariant value) {
    if (index < array->length) {
        varDestroy(array->elements[index]);
        array->elements[index] = value;
        return true;
    }
    return false;
}


