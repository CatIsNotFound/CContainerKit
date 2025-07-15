
#pragma once
#ifndef CVECTORSUITE_CVARIANT_H
#define CVECTORSUITE_CVARIANT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>

typedef enum Types {
    TYPE_NULL,           // 空值
    TYPE_BOOL,           // 布尔值
    TYPE_INT8,           // 有符号8位整数
    TYPE_INT16,          // 有符号16位整数
    TYPE_INT32,          // 有符号32位整数
    TYPE_INT64,          // 有符号64位整数
    TYPE_UINT8,          // 无符号8位整数
    TYPE_UINT16,         // 无符号16位整数
    TYPE_UINT32,         // 无符号32位整数
    TYPE_UINT64,         // 无符号64位整数
    TYPE_FLOAT,          // 单精度浮点数
    TYPE_DOUBLE,         // 双精度浮点数
    TYPE_LONG_DOUBLE,    // 扩展精度浮点数
    TYPE_POINTER,        // 通用指针
    TYPE_STRING,         // 字符串 (const char*)
    TYPE_STRUCT,         // 结构体
    TYPE_ENUM,           // 枚举
    TYPE_FUNCTION,       // 函数指针
    TYPE_CUSTOM          // 自定义
} dataType;

typedef struct Variant CVariant;

typedef struct VStruct {
    void* data;
    const char* type_name;
} VStruct;

typedef struct VEnum {
    int8_t value;
    const char* type_name;
} VEnum;

typedef void (*destructorFunc)(void *);

typedef struct VCustom {
    void* data;
    const char* type_name;
    destructorFunc destructor;
} VCustom;

struct Variant {
    void*    value;     // 数据值
    uint8_t  data_type; // 数据类型
};

#include "CDebug.h"

const char* _getTypeName(dataType d_type);
const char* _varTypeName(CVariant* variant);
#define varTypeName(variant)    _varTypeName(&variant)

CVariant _varEmpty();
CVariant _varBool(bool value);
CVariant _varInt8(int8_t value);
CVariant _varUInt8(uint8_t value);
CVariant _varInt16(int16_t value);
CVariant _varUInt16(uint16_t value);
CVariant _varInt32(int32_t value);
CVariant _varUInt32(uint32_t value);
CVariant _varInt64(int64_t value);
CVariant _varUInt64(uint64_t value);
CVariant _varFloat(float* value);
CVariant _varDouble(double* value);
CVariant _varLongDouble(long double* value);
CVariant _varPointer(void* value);
CVariant _varString(const char* value);
CVariant _varStruct(void *value, const char *type_name);
CVariant _varEnum(int8_t value, const char *type_name);
CVariant _varFunction(void (*value)(void*));
CVariant _varCustom(void *value, const char *type_name, void (*destructor)(void *));

#define varBool(value)      _varBool(value)
#define varChar(value)      _varInt8(value)
#define varUChar(value)     _varUInt8(value)
#define varShort(value)     _varInt16(value)
#define varUShort(value)    _varUInt16(value)
#define varInt(value)       _varInt32(value)
#define varUInt(value)      _varUInt32(value)
#define varLongLong(value)  _varInt64(value)
#define varULongLong(value) _varUInt64(value)
#define varFloat(value)     _varFloat(&value)
#define varDouble(value)    _varDouble(&value)
#define varLongDouble(value) _varLongDouble(&value)
#define varPointer(value)   _varPointer((void*)value)
#define varString(value)    _varString(value)
#define varStruct(value, type_name)  _varStruct((void*)&value, type_name)
#define varEnum(value, type_name)    _varEnum((int8_t)value, type_name)
#define varFunction(function)        _varFunction(function)
#define varCustom(value, type_name, destructor)   _varCustom(value, type_name, destructor)

void _varBoolModifyValue(CVariant* variant, bool new_value);
void _varIntModifyValue(CVariant* variant, int64_t new_value);
void _varUIntModifyValue(CVariant* variant, uint64_t new_value);

#define varBoolModifyData(variant, new_value) _varIntModifyValue(&variant, new_value)
#define varIntModifyData(variant, new_value)  _varIntModifyValue(&variant, new_value)
#define varUIntModifyData(variant, new_value) _varUIntModifyValue(&variant, new_value)

static void varDestroyPointer(CVariant* variant) {
    if (variant->data_type == TYPE_POINTER) {
        free(variant->value);
    }
}

static void varDestroyCustom(CVariant* variant) {
    if (variant->data_type == TYPE_CUSTOM) {
        ((VCustom*)(variant->value))->destructor(variant->value);
    }
}

bool _varBoolValue(CVariant* variant);
int8_t _varInt8Value(CVariant* variant);
uint8_t _varUInt8Value(CVariant* variant);
int16_t _varInt16Value(CVariant* variant);
uint16_t _varUInt16Value(CVariant* variant);
int32_t _varInt32Value(CVariant* variant);
uint32_t _varUInt32Value(CVariant* variant);
int64_t _varInt64Value(CVariant* variant);
uint64_t _varUInt64Value(CVariant* variant);
float* _varFloatPtr(CVariant* variant);
double* _varDoublePtr(CVariant* variant);
long double* _varLongDoublePtr(CVariant* variant);
void* _varPtr(CVariant* variant);
const char* _varStringData(CVariant* variant);
void* _varStructPtr(CVariant* variant);

#define varBoolData(variant)       _varBoolValue(&variant)
#define varCharData(variant)       _varInt8Value(&variant)
#define varUCharData(variant)      _varUInt8Value(&variant)
#define varShortData(variant)      _varInt16Value(&variant)
#define varUShortData(variant)     _varUInt16Value(&variant)
#define varIntData(variant)        _varInt32Value(&variant)
#define varUIntData(variant)       _varUInt32Value(&variant)
#define varLongLongData(variant)   _varInt64Value(&variant)
#define varULongLongData(variant)  _varUInt64Value(&variant)
#define varFloatData(variant)      *(_varFloatPtr(&variant))
#define varDoubleData(variant)     *(_varDoublePtr(&variant))
#define varLongDoubleData(variant) *(_varLongDoublePtr(&variant))
#define varStringData(variant)     _varStringData(&variant)
#define varPointerData(variant, ptr_type)    (ptr_type *)_varPtr(&variant)
#define varStructPtr(variant, struct_type)   (struct_type *)_varStructPtr(&variant)
#define varStructData(variant, struct_type)  *(varStructPtr(variant, struct_type))

void _printVarData(CVariant* variant);
#define printVarData(variant)      _printVarData(&variant)

#define N_POS SIZE_MAX

#endif //CVECTORSUITE_CVARIANT_H
