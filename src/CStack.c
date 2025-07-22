#include "CContainerKit/CStack.h"

CStack stackInit(uint32_t length) {
    CStack new_stack;
    new_stack.my_stack = vectorInit(length);
    return new_stack;
}

CStack stackInitType(dataType data_type, uint32_t length) {
    CStack new_stack;
    new_stack.my_stack = vectorInitType(data_type, length);
    return new_stack;
}

CStack stackList(size_t length, ...) {
    CStack new_stack;
    new_stack.my_stack = vectorInit(length);
    va_list s_list;
    va_start(s_list, length);
    for (size_t i = 0; i < length; ++i) {
        CVariant var = va_arg(s_list, CVariant);
        vecModify(new_stack.my_stack, i, var);
    }
    va_end(s_list);
    return new_stack;
}

CVector _stkToVector(CStack* stack, bool delete_stack, bool* ok) {
    if (!stack) {
        if (ok) *ok = false;
        throwError("Stack to Vector: The specified stack is not valid!");
        return vectorInit(0);
    }
    CVector new_vector = vectorInit(_stackSize(stack));
    CVariant var;
    forEachVecElements(var, stack->my_stack) {
        vecModify(new_vector, i, var);
    }
    if (delete_stack) {
        _destroyStack(stack);
    }
    if (ok) *ok = true;
    return new_vector;
}

CStack _vecToStack(CVector* vector, bool delete_vector, bool* ok) {
    if (!vector) {
        if (ok) *ok = false;
        CStack null_stack = {};
        return null_stack;
    }
    CStack new_stack = stackInit(vector->length);
    CVariant var;
    forEachVecElePtr(var, vector) {
        vecModify(new_stack.my_stack, i, var);
    }
    if (delete_vector) {
        _destroyVector(vector);
    }
    if (ok) *ok = true;
    return new_stack;
}

void _resizeStack(CStack* stack, uint32_t new_size) {
    _resizeVector(&stack->my_stack, new_size);
}

void _destroyStack(CStack* stack) {
    destroyVector(stack->my_stack);
}

void _deleteStack(CStack* stack) {
    deleteVector(stack->my_stack);
}

void _stackPush(CStack* stack, CVariant new_value) {
    vecPushBack(stack->my_stack, new_value);
}

void _stackPushFromArray(CStack* stack, CArray* array) {
    vecPushBackArray(stack->my_stack, *array);
}

void _stackPop(CStack* stack) {
    if (stack->my_stack.length) vecPopBack(stack->my_stack);
}

void _stackClear(CStack* stack) {
    if (stack->my_stack.length) vecClear(stack->my_stack);
}

bool _stackIsElementContain(CStack* stack, CVariant key) {
    return vecIsContain(stack->my_stack, key, 0);
}

CVariant _stackAt(CStack* stack, size_t index) {
    if (index >= stack->my_stack.length) return varEmpty();
    return vecAt(stack->my_stack, index);
}

CVariant _stackTop(CStack* stack) {
    if (stack->my_stack.length) return stack->my_stack.elements[stack->my_stack.length - 1];
    else return varEmpty();
}

uint32_t _stackIndexOf(CStack* stack, CVariant key, size_t start_pos) {
    return vecIndexOf(stack->my_stack, key, start_pos);
}

uint32_t _stackSize(CStack* stack) {
    return stack->my_stack.length;
}

uint32_t _stackCapacity(CStack* stack) {
    return stack->my_stack.capacity;
}

