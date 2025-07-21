#include "CContainerKit/CVector.h"

CVector vectorInit(size_t length) {
    CVector new_vector;
    new_vector.length = length;
    new_vector.capacity = length * 2;
    new_vector.elements = (CVariant*) calloc(length * 2, sizeof(CVariant));
    // Allocation failed
    if (new_vector.elements == NULL) {
        new_vector.length = 0;
        new_vector.capacity = 0;
        return new_vector;
    }
    for (size_t i = 0; i < length * 2; ++i) {
        new_vector.elements[i].data_type = TYPE_NULL;
        new_vector.elements[i].value = (void*)0;
    }
    return new_vector;
}

CVector vectorInitType(dataType data_type, size_t length) {
    CVector new_vector;
    new_vector.length = length;
    new_vector.capacity = length * 2;
    new_vector.elements = (CVariant*) calloc(length * 2, sizeof(CVariant));
    if (new_vector.elements == NULL) {
        new_vector.length = 0;
        new_vector.capacity = 0;
        return new_vector;
    }
    for (size_t i = 0; i < length * 2; ++i) {
        new_vector.elements[i].data_type = data_type;
        new_vector.elements[i].value = (void*)0;
    }
    return new_vector;
}

CVector vectorList(size_t length, ...) {
    CVector new_vector;
    new_vector.length = length;
    new_vector.capacity = length * 2;
    new_vector.elements = (CVariant*) calloc(length * 2, sizeof(CVariant));
    va_list a_list;
    va_start(a_list, length);
    for (size_t i = 0; i < length * 2; ++i) {
        if (i < length) {
            CVariant var = va_arg(a_list, CVariant);
            new_vector.elements[i].data_type = var.data_type;
            new_vector.elements[i].value = var.value;
        } else {
            new_vector.elements[i].data_type = TYPE_NULL;
            new_vector.elements[i].value = (void*)0;
        }
    }
    va_end(a_list);
    return new_vector;
}

CVector _arrayToVector(CArray* array, bool delete_array, bool* ok) {
    CVector new_vector; static CVector v_null;
    if (!array) {
        if (ok) *ok = false;
        return v_null;
    }
    new_vector.length = array->length;
    new_vector.capacity = array->length * 2;
    new_vector.elements = (CVariant*) calloc(array->length * 2, sizeof(CVariant));
    if (new_vector.elements == NULL) {
        if (ok) *ok = false;
        return v_null;
    }
    for (size_t i = 0; i < array->length * 2; ++i) {
        if (i < array->length) {
            new_vector.elements[i].data_type = array->elements[i].data_type;
            new_vector.elements[i].value = array->elements[i].value;
        } else {
            new_vector.elements[i].data_type = TYPE_NULL;
            new_vector.elements[i].value = (void*)0;
        }
    }
    if (delete_array) {
        for (size_t i = 0; i < array->length; ++i) {
            array->elements[i] = _varEmpty();
        }
        _destroyArray(array);
    }
    if (ok) *ok = true;
    return new_vector;
}

CArray _vectorToArray(CVector* vector, bool delete_vector, bool* ok) {
    CArray new_array; static CArray null_array;
    if (!vector) { if (ok) *ok = false; return null_array; }
    new_array.length = vector->length;
    new_array.elements = (CVariant*) calloc(vector->length, sizeof(CVariant));
    if (!new_array.elements) { if (ok) *ok = false; return null_array; }
    for (size_t i = 0; i < vector->length; ++i) {
        new_array.elements[i] = vector->elements[i];
    }
    if (delete_vector) {
        for (size_t i = 0; i < vector->length; ++i) {
            vector->elements[i] = _varEmpty();
        }
        _destroyVector(vector);
    }
    if (ok) *ok = true;
    return new_array;
}

void _expandVector(CVector *vector) {
    size_t new_size = (vector->capacity == 0 ? 2 : vector->capacity * 2);
    _resizeVector(vector, new_size);
}

void _resizeVector(CVector* vector, size_t new_size) {
    if (!vector) return;
    if (new_size < vector->capacity) {
        throwError("Resize failed: The new size is smaller than the original size.");
        return;
    }
    CVariant* new_space = (CVariant*) calloc(new_size, sizeof(CVariant));
    for (size_t i = 0; i < vector->length; ++i) {
        new_space[i] = vector->elements[i];
    }
    free(vector->elements);
    vector->elements = new_space;
    vector->capacity = new_size;
}

void _destroyVector(CVector* vector) {
    if (vector && vector->elements) {
        free(vector->elements);
        vector->elements = NULL;
        vector->length = 0;
        vector->capacity = 0;
    }
}

void _deleteVector(CVector* vector) {
    if (vector) {
        for (size_t i = 0; i < vector->length; ++i) {
            varDestroy(vector->elements[i]);
        }
        _destroyVector(vector);
    }
}

void _vectorInsert(CVector* vector, size_t index, CVariant new_value) {
    if (vector->length >= vector->capacity) {
        _expandVector(vector);
    }
    for (size_t i = 0; i < vector->length - index; ++i) {
        vector->elements[vector->length - i] = vector->elements[vector->length - i - 1];
    }
    vector->elements[index] = new_value;
    vector->length += 1;
}

void _vectorInsertFromArray(CVector* vector, size_t index, CArray* array) {
    size_t steps = array->length;
    size_t new_size = vector->length + array->length;
    if (new_size >= vector->capacity) {
        _resizeVector(vector, new_size * 2);
    }
    for (size_t i = 0; i < new_size - index; ++i) {
        vector->elements[new_size - i] = vector->elements[new_size - i - steps];
    }
    for (size_t i = 0; i < array->length; ++i) {
        vector->elements[index + i] = array->elements[i];
    }
    vector->length += array->length;
}

void _vectorRemove(CVector* vector, size_t start_pos, size_t count) {
    _vectorFill(vector, start_pos, count, _varEmpty());
    for (size_t i = start_pos; i < vector->length - count; ++i) {
        vector->elements[i] = vector->elements[i + count];
    }
    vector->length -= count;
}

void _vectorClear(CVector *vector) {
    _vectorFill(vector, 0, vector->length, _varEmpty());
    vector->length = 0;
}

bool _vectorIsElementContain(CVector* vector, CVariant key, size_t start_pos) {
    for (size_t i = start_pos; i < vector->length; ++i) {
        if (key.data_type != vector->elements[i].data_type) continue;
        if (key.value != vector->elements[i].value) continue;
        return true;
    }
    return false;
}

size_t _vectorIndexOf(CVector *vector, CVariant element, size_t start_pos) {
    for (size_t i = start_pos; i < vector->length; ++i) {
        if (element.data_type != vector->elements[i].data_type) continue;
        if (element.value != vector->elements[i].value) continue;
        return i;
    }
    return N_POS;
}

CVariant _vectorAt(CVector* vector, size_t index) {
    if (index < vector->length) {
        return vector->elements[index];
    }
    return _varEmpty();
}

bool _vectorModify(CVector* vector, size_t index, CVariant new_value) {
    if (index < vector->length) {
        vector->elements[index] = new_value;
        return true;
    }
    return false;
}

void _vectorFill(CVector* vector, size_t start_pos, uint32_t count, CVariant new_value) {
    size_t end_pos = start_pos + count - 1;
    if (end_pos >= vector->length) end_pos = vector->length;
    for (size_t i = start_pos; i <= end_pos; ++i) {
        varDestroy(vector->elements[i]);
        vector->elements[i] = new_value;
    }
}

CVector _vectorSubVec(CVector* vector, size_t start_pos, uint32_t count) {
    CVector sub_vec;
    sub_vec.elements = (CVariant*) calloc(count, sizeof(CVariant));
    sub_vec.length = count;
    sub_vec.capacity = count;
    size_t end_pos = start_pos + count - 1;
    size_t real_count = 0;
    if (end_pos >= vector->length) end_pos = vector->length;
    for (size_t i = start_pos; i <= end_pos; ++i) {
        sub_vec.elements[i - start_pos] = vector->elements[i];
        real_count += 1;
    }
    if (real_count < count) {
        sub_vec.length = real_count;
        sub_vec.capacity = real_count;
    }
    return sub_vec;
}
