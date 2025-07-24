
#pragma once
#ifndef CCONTAINERKIT_CSTACK_H
#define CCONTAINERKIT_CSTACK_H
#include "CVector.h"

typedef struct Stack {
    CVector my_stack;
} CStack;

CStack stackInit(uint32_t length);
CStack stackInitType(dataType data_type, uint32_t length);
CStack stackList(size_t length, ...);
CVector _stkToVector(CStack* stack, bool delete_stack, bool* ok);
CStack _vecToStack(CVector* vector, bool delete_vector, bool* ok);
void _resizeStack(CStack* stack, uint32_t new_size);
void _destroyStack(CStack* stack);
void _deleteStack(CStack* stack);
void _stackPush(CStack* stack, CVariant new_value);
void _stackPushFromArray(CStack* stack, CArray* array);
void _stackPop(CStack* stack);
void _stackClear(CStack* stack);
bool _stackIsElementContain(CStack* stack, CVariant key);
CVariant _stackAt(CStack* stack, size_t index);
CVariant _stackTop(CStack* stack);
uint32_t _stackIndexOf(CStack* stack, CVariant key, size_t start_pos);
uint32_t _stackSize(CStack* stack);
uint32_t _stackCapacity(CStack* stack);


#define stkToVector(stack, delete_stack, ok)              _stkToVector(&stack, delete_stack, ok)
#define vecToStack(vector, delete_vector, ok)             _vecToStack(&vector, delete_vector, ok)
#define resizeStack(stack, new_size)                      _resizeStack(&stack, new_size)
#define destroyStack(stack)                               _destroyStack(&stack)
#define deleteStack(stack)                                _deleteStack(&stack)
#define stkPush(stack, var)                               _stackPush(&stack, var)
#define stkPushFromArray(stack, array)                    _stackPushFromArray(&stack, &array)
#define stkPop(stack)                                     _stackPop(&stack)
#define stkClear(stack)                                   _stackClear(&stack)
#define stkIsContain(stack, key)                          _stackIsElementContain(&stack, key)
#define stkAt(stack, index)                               _stackAt(&stack, index)
#define stkTop(stack)                                     _stackTop(&stack)
#define stkIndexOf(stack, var, start_pos)                 _stackIndexOf(&stack, var, start_pos)
#define stkSize(stack)                                    _stackSize(&stack)
#define stkLength(stack)                                  stkSize(stack)
#define stkCapacity(stack)                                _stackCapacity(&stack)

#define forEachStkElements(item, stack)          \
    item = stack.my_stack.elements[0];           \
    for (size_t i = 0; i < _stackSize(&stack); ++i, item = stack.my_stack.elements[i])

#define forEachStkElePtr(item, stack)             \
    item = stack->my_stack.elements[0];           \
    for (size_t i = 0; i < _stackSize(stack); ++i, item = stack->my_stack.elements[i])

#endif //CCONTAINERKIT_CSTACK_H
